#include "element.h"
#include "application.h"
#include "collection.h"
#include "config.h"
#include "txt_exporter.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace todo;

application::application(int argc, char *argv[])
{
  m_colors["reset"]       = "\x1b[0m";
  m_colors["bright"]      = "\x1b[1m";
  m_colors["underscore"]  = "\x1b[4m";
  m_colors["black"]       = "\x1b[30m";
  m_colors["red"]         = "\x1b[31m";
  m_colors["green"]       = "\x1b[32m";
  m_colors["yellow"]      = "\x1b[33m";
  m_colors["blue"]        = "\x1b[34m";
  m_colors["magenta"]     = "\x1b[35m";
  m_colors["cyan"]        = "\x1b[36m";
  m_colors["white"]       = "\x1b[37m";

  m_exporters["txt"]      = new txt_exporter();

  status = fill_parameters(argc, argv);
}

application::~application()
{
  if (m_config) delete m_config;
}

std::string application::print_color(std::string const & l_color, std::string const & l_string, bool bright, bool underline)
{
  std::string ret;
  if (not m_parameters.m_monochrome and not m_config->isMonochrome()) {
    if (underline) ret += m_colors["underscore"];
    if (bright) ret += m_colors["bright"];
    ret += m_colors[l_color];
  }

  ret += l_string;

  if (not m_parameters.m_monochrome and not m_config->isMonochrome())
    ret += m_colors["reset"];

  return ret;
}

std::string application::print_color(std::string const & l_color, int l_number, bool bright, bool underline)
{
  char l_buffer[1024] = { 0 };
  sprintf(l_buffer, "%02d", l_number);
  std::string ret;
  if (not m_parameters.m_monochrome and not m_config->isMonochrome()) {
    if (underline) ret += m_colors["underscore"];
    if (bright) ret += m_colors["bright"];
    ret += m_colors[l_color];
  }

  ret += std::string(l_buffer);

  if (not m_parameters.m_monochrome and not m_config->isMonochrome())
    ret += m_colors["reset"];

  return ret;
}

bool application::fill_parameters(int argc, char *argv[])
{
  bool l_ret(true);
  int l_index(1);

  m_config = 0;

  // Sane defaults
  m_parameters.m_filling_body = false;
  m_parameters.m_todorc = std::string(getenv("HOME")) + std::string("/.halirc");
  m_parameters.m_verbose = false;
  m_parameters.m_priority = 100;
  m_parameters.m_note_id = 1000;
  m_parameters.m_monochrome = false;
  m_parameters.m_confirmation = false;
  m_appname = std::string(argv[0]);

  while (argv[l_index]) {
    std::string l_param(argv[l_index]);

    if (m_parameters.m_action.empty())
      m_parameters.m_action = l_param;

    else if (l_param == "-h" or l_param == "--help" or l_param == "-v" or l_param == "--version")
    {
      l_ret = false;
    }

    else if (l_param == "-p" or l_param == "--priority")
    {
      if (++l_index < argc)
        m_parameters.m_priority = atoi(argv[l_index]);
      else
      {
        l_ret = false;
        m_error = "Missing ID for priority";
      }
    }

    else if (l_param == "-b" or l_param == "--body")
      m_parameters.m_filling_body = true;

    else if (l_param == "-t" or l_param == "--title")
      m_parameters.m_filling_body = false;

    else if (l_param == "-n" or l_param == "--note")
    {
      if (++l_index < argc)
        m_parameters.m_note_id = atoi(argv[l_index]);
      else
      {
        l_ret = false;
        m_error = "Missing ID for note";
      }
    }

    else if (l_param == "-r" or l_param == "--todorc")
    {
      if (++l_index < argc)
        m_parameters.m_todorc = std::string(argv[l_index]);
    }

    else if (l_param == "-d" or l_param == "--tododb")
    {
      if (++l_index < argc)
        m_parameters.m_tododb = std::string(argv[l_index]);
    }
    else if (l_param == "-m" or l_param == "--monochrome")
    {
      m_parameters.m_monochrome = true;
    }
    else if (l_param == "-c" or l_param == "--confirm")
    {
      m_parameters.m_confirmation = true;
    }

    else if (m_parameters.m_action == "export" or m_parameters.m_action == "e")
    {
      if (l_param == "-o" or l_param == "--output") {
        if (++l_index < argc)
          m_parameters.m_exporter.m_file = std::string(argv[l_index]);
      }
      else if (m_exporters.find(l_param) != m_exporters.end())
        m_parameters.m_exporter.m_type = l_param;
    }

    else if (not m_parameters.m_filling_body)
    {
      if (not m_parameters.m_title.empty())
        m_parameters.m_title += " ";
      m_parameters.m_title += std::string(argv[l_index]);
    }

    else
    {
      if (not m_parameters.m_body.empty())
        m_parameters.m_body += " ";
      m_parameters.m_body += std::string(argv[l_index]);
    }

    l_index++;
  }

  m_action = kList;

  // Choose the proper action
  if (m_parameters.m_action == "insert" or m_parameters.m_action == "i")
    m_action = kInsert;
  else if (m_parameters.m_action == "delete" or m_parameters.m_action == "d")
    m_action = kDelete;
  else if (m_parameters.m_action == "modify" or m_parameters.m_action == "m")
    m_action = kModify;
  else if (m_parameters.m_action == "search" or m_parameters.m_action == "s")
    m_action = kSearch;
  else if (m_parameters.m_action == "export" or m_parameters.m_action == "e")
    m_action = kExport;
  else if (m_parameters.m_action == "help" or
           m_parameters.m_action == "-h" or
           m_parameters.m_action == "--help" or
           m_parameters.m_action == "-v" or
           m_parameters.m_action == "--version") {
    l_ret = false;
  }

  if (m_action == kInsert and m_parameters.m_title.empty())
  {
    m_error = "Missing title for note!";
    l_ret = false;
  }

  if (l_ret) {
    m_config = new config(m_parameters.m_todorc);
    if (not m_config->parse_config()) {
      m_error += print_color("red", "ERROR", true, true);
      m_error += ": missing configuration file in ";
      m_error += print_color("yellow", m_parameters.m_todorc, true, true);
      l_ret = false;
    }
  }

  return l_ret;
}

void application::print_usage()
{
  if (not m_error.empty())
    std::cerr << m_error << std::endl;

  else
  {
    printf("     -[ HALI version %s ]-\n", TODO_VERSION);
    printf("Usage: %s <action> [parameters]\n", m_appname.c_str());
    printf("  List of available actions\n");
    printf("         list   | l                  list all notes in the db\n");
    printf("       insert   | i <parameters>     insert a new note\n");
    printf("       modify   | m <parameters>     modify a given note\n");
    printf("       delete   | d <parameters>     delete a given note\n");
    printf("       search   | s <parameters>     search for given text in notes\n");
    printf("       export   | e <parameters>     exports the current db in a different format\n");
    printf("\n");
    printf(" List of available parameters\n");
    printf("       --note   | -n id              specify the note id\n");
    printf("      --title   | -t text            the text that follows is the title\n");
    printf("       --body   | -b text            the text that follows is the body\n");
    printf(" --monochrome   | -m                 print a monochrome version\n");
    printf("   --priority   | -p id              priority of the new note\n");
    printf("     --todorc   | -r file            use this todorc file\n");
    printf("     --tododb   | -d file            use this db of notes\n");
    printf("    --version   | -v                 print version and exit\n");
    printf("    --confirm   | -c                 ask for confirmation before deleting \n");
    printf("\n");
    printf(" List of available exporters\n");
    printf("         txt    |                    text file exporter\n");
    //printf("         xml    |                    XML file exporter\n");
    //printf("        html    |                    HTML file exporter\n");
    //printf("         csv    |                    CSV file exporter\n");
    printf("\n");
    printf(" List of parameters for exporting\n");
    printf("     --output   | -o file            outputs to given file name\n");
    printf("\n");
  }
}

void application::pretty_print_element(todo::element const & p_element)
{
  if (m_parameters.m_monochrome) {
    fprintf(stdout, "[%02d] %s", p_element.m_index, p_element.m_title.c_str());
    if (not p_element.m_body.empty())
      fprintf(stdout, " : %s", p_element.m_body.c_str());

    switch (p_element.m_priority) {
      case 1:
        fprintf(stdout, " : %s\n", "medum priority");
        break;
      case 2:
        fprintf(stdout, " : %s\n", "high priority");
        break;
      default:
        fprintf(stdout, " : %s\n", "low priority");
        break;
    }
  }
  else {
    fprintf(stdout, "[%s] %s",
        print_color((*m_config)[NOTE_ID_COLOR], p_element.m_index).c_str(),
        print_color((*m_config)[NOTE_TITLE_COLOR], p_element.m_title).c_str());
    if (not p_element.m_body.empty())
      fprintf(stdout, " : %s",
          print_color((*m_config)[NOTE_BODY_COLOR], p_element.m_body).c_str());

    switch (p_element.m_priority) {
      case 1:
        fprintf(stdout, " : %s\n", print_color((*m_config)[PRIORITY_DEFAULT_COLOR], "medium priority").c_str());
        break;
      case 2:
        fprintf(stdout, " : %s\n", print_color((*m_config)[PRIORITY_HIGH_COLOR], "high priority", true, true).c_str());
        break;
      default:
        fprintf(stdout, " : %s\n", print_color((*m_config)[PRIORITY_LOW_COLOR], "low priority").c_str());
        break;
    }
  }
}

int application::run()
{
  if (not status) {
    print_usage();
    return 127;
  }

  std::string l_db;

  if (m_parameters.m_tododb.empty())
  {
    l_db = (*m_config)[FILE_CONFIG_FILE];
  }

  else
    l_db = m_parameters.m_tododb;

  todo::collection l_collection(l_db);
  l_collection.read_file();
  if (m_action != kInsert)
    fprintf(stdout, "You have %s todos\n", print_color((*m_config)[NOTE_COUNT_COLOR], l_collection.size()).c_str());

  switch (m_action)
  {
    case kList:
    {
      if (m_parameters.m_priority > 2) {
        todo::collection const & l_sorted = l_collection.sort_by_priority();
        std::for_each(l_sorted.begin(), l_sorted.end(), [&](todo::element const & p_element)->void {
          pretty_print_element(p_element);
        });
      }
      else {
        todo::collection const & l_priority = l_collection.retrieve_notes_by_priority(m_parameters.m_priority);
        std::for_each(l_priority.begin(), l_priority.end(), [&](todo::element const & p_element)->void {
          pretty_print_element(p_element);
        });
      }
      break;
    }
    case kModify:
    {
      bool l_proceed(ask_for_confirmation(l_collection, "modify"));

      if (m_parameters.m_note_id < l_collection.size() and l_proceed) {
        todo::element & l_element = l_collection[m_parameters.m_note_id];
        if (m_parameters.m_priority < 3)
          l_element.m_priority = m_parameters.m_priority;
        if (not m_parameters.m_title.empty())
          l_element.m_title = m_parameters.m_title;
        if (not m_parameters.m_body.empty())
          l_element.m_body = m_parameters.m_body;
        if (m_parameters.m_body == "--")
          l_element.m_body.clear();


        pretty_print_element(l_element);
      }
      else if (l_proceed) {
        m_error = "Note out of range";
        print_usage();
        return 127;
      }

      break;
    }
    case kInsert:
    {
      todo::element l_element(m_parameters.m_title, m_parameters.m_body);
      if (m_parameters.m_priority < 3)
        l_element.m_priority = m_parameters.m_priority;
      l_collection.push_back(l_element);
      pretty_print_element(l_element);
      break;
    }
    case kDelete:
    {
      bool l_proceed(ask_for_confirmation(l_collection, "delete"));

      if (m_parameters.m_note_id < l_collection.size() && l_proceed) {
        l_collection.erase(l_collection.begin() + m_parameters.m_note_id);
        fprintf(stdout, "Note %s erased -- you now have %s notes\n",
            print_color("red", m_parameters.m_note_id).c_str(),
            print_color((*m_config)[NOTE_COUNT_COLOR], l_collection.size()).c_str());
      }
      else if (l_proceed) {
        m_error = "Note out of range";
        print_usage();
        return 127;
      }

      break;
    }
    case kSearch:
    {
      todo::collection l_search = l_collection.retrieve_notes_by_text(m_parameters.m_title);
      if (l_search.empty()) {
        m_error += print_color("yellow", "WARNING", true, false);
        m_error += ": the search for ";
        m_error += print_color("yellow", m_parameters.m_title);
        m_error += " didn't return any result.";
        print_usage();
        return 0;
      }
      else {
        std::for_each(l_search.begin(), l_search.end(), [&](todo::element & l_element)->void {
          if (not m_parameters.m_monochrome and not m_config->isMonochrome()) {
            l_element.m_title.replace(l_element.m_title.find("$BEGIN$"), 7, m_colors[(*m_config)[NOTE_SEARCH_COLOR]]);
            l_element.m_title.replace(l_element.m_title.find("$END$"), 5, m_colors[(*m_config)[NOTE_TITLE_COLOR]]);
          }
          else {
            l_element.m_title.replace(l_element.m_title.find("$BEGIN$"), 7, "");
            l_element.m_title.replace(l_element.m_title.find("$END$"), 5, "");
          }
          pretty_print_element(l_element);
        });
      }
      break;
    }
    case kExport:
    {
      if (not m_parameters.m_exporter.m_type.empty() and not m_parameters.m_exporter.m_file.empty()) {
        exporter * l_exporter = m_exporters[m_parameters.m_exporter.m_type];
        l_exporter->set_file(m_parameters.m_exporter.m_file);
        l_exporter->init();
        std::for_each(l_collection.begin(), l_collection.end(), [&](todo::element const & p_el)->void {
          l_exporter->process_note(p_el);
        });

        l_exporter->finalize();
      }

      break;
    }
  }

  l_collection.write_file();

  return 0;
}

bool application::ask_for_confirmation(todo::collection const & p_collection, std::string const & p_text)
{
  bool l_res(true);
  if ((m_parameters.m_confirmation or
      m_config->isAskForConfirmation()) and
      m_parameters.m_note_id < p_collection.size())
  {
    std::string l_reply;
    l_res = false;
    fprintf(stdout, "Do you really want to %s the following note\n",
        print_color("yellow", p_text, true, true).c_str());

    pretty_print_element(p_collection[m_parameters.m_note_id]);

    fprintf(stdout, "%s/%s to confirm, any other key to abort: ",
        print_color("yellow", "Y", true, true).c_str(),
        print_color("yellow", "y", true, true).c_str());

    std::cin >> l_reply;

    if (l_reply == "y" or l_reply == "Y") l_res = true;
  }

  return l_res;
}

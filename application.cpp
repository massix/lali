#include "element.h"
#include "application.h"
#include "collection.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace todo;

application::application(int argc, char *argv[]) : 
  status(fill_parameters(argc, argv))
{
  m_colors["reset"]       = "\x1b[0m";
  m_colors["bright"]      = "\x1b[1m";
  m_colors["underscore"]  = "\x1b[4m";
  m_colors["black"]     = "\x1b[30m";
  m_colors["red"]       = "\x1b[31m";
  m_colors["green"]     = "\x1b[32m";
  m_colors["yellow"]    = "\x1b[33m";
  m_colors["blue"]      = "\x1b[34m";
  m_colors["magenta"]   = "\x1b[35m";
  m_colors["cyan"]      = "\x1b[36m";
  m_colors["white"]     = "\x1b[37m";

}

application::~application()
{
  if (m_config) delete m_config;
}

std::string application::printColor(std::string const & l_color, std::string const & l_string, bool bright, bool underline)
{
  std::string ret;
  if (underline) ret += m_colors["underscore"];
  if (bright) ret += m_colors["bright"];
  ret += m_colors[l_color];
  ret += l_string;
  ret += m_colors["reset"];

  return ret;
}

std::string application::printColor(std::string const & l_color, int l_number, bool bright, bool underline)
{
  char l_buffer[1024] = { 0 };
  sprintf(l_buffer, "%02d", l_number);
  std::string ret;
  if (underline) ret += m_colors["underscore"];
  if (bright) ret += m_colors["bright"];
  ret += m_colors[l_color];
  ret += std::string(l_buffer);
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
  m_parameters.m_todorc = std::string(getenv("HOME")) + std::string("/.todorc");
  m_parameters.m_verbose = false;
  m_parameters.m_priority = 100;
  m_parameters.m_note_id = 1000;
  m_appname = std::string(argv[0]);

  while (argv[l_index]) {
    std::string l_param(argv[l_index]);

    if (m_parameters.m_action.empty())
      m_parameters.m_action = l_param;

    else if (l_param == "-h" or l_param == "--help")
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
  else if (m_parameters.m_action == "help" or m_parameters.m_action == "-h" or m_parameters.m_action == "--help") {
    l_ret = false;
  }

  if (m_action == kInsert and m_parameters.m_title.empty())
  {
    m_error = "Missing title for note!";
    l_ret = false;
  }

  if (l_ret) {
    m_config = new config(m_parameters.m_todorc);
    l_ret = m_config->parse_config();
  }

  return l_ret;
}

void application::print_usage()
{
  if (not m_error.empty())
    std::cerr << m_error << std::endl;

  printf("Usage: %s <action> [parameters]\n", m_appname.c_str());
  printf("  List of available actions\n");
  printf("    list        | l                  list all notes in the db\n");
  printf("  insert        | i <parameters>     insert a new note\n");
  printf("  modify        | m <parameters>     modify a given note\n");
  printf("  delete        | d <parameters>     delete a given note\n");
  printf("\n");
  printf(" List of available parameters\n");
  printf("     --note     | -n id              specify the note id\n");
  printf("    --title     | -t text            the text that follows is the title\n");
  printf("     --body     | -b text            the text that follows is the body\n");
  printf(" --priority     | -p id              priority of the new note\n");
  printf("   --todorc     | -r file            use this todorc file\n");
  printf("   --tododb     | -d file            use this db of notes\n");
}

void application::pretty_print_element(todo::element const & p_element, uint32_t p_index)
{
  fprintf(stdout, "[%s] %s", 
      printColor((*m_config)[NOTE_ID_COLOR], p_index).c_str(), 
      printColor((*m_config)[NOTE_TITLE_COLOR], p_element.m_title).c_str());
  if (not p_element.m_body.empty())
    fprintf(stdout, " : %s", 
        printColor((*m_config)[NOTE_BODY_COLOR], p_element.m_body).c_str());

  switch (p_element.m_priority) {
    case 1:
      fprintf(stdout, " : %s\n", printColor((*m_config)[PRIORITY_DEFAULT_COLOR], "medium priority").c_str());
      break;
    case 2:
      fprintf(stdout, " : %s\n", printColor((*m_config)[PRIORITY_HIGH_COLOR], "high priority", true, true).c_str());
      break;
    default:
      fprintf(stdout, " : %s\n", printColor((*m_config)[PRIORITY_LOW_COLOR], "low priority").c_str());
      break;
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
  fprintf(stdout, "You have %s todos\n", printColor((*m_config)[NOTE_ID_COLOR], l_collection.size()).c_str());

  switch (m_action)
  {
    case kList:
    {
      todo::collection::const_iterator l_iterator = l_collection.begin();
      for (uint32_t l_idx = 0; l_iterator != l_collection.end(); ++l_iterator, l_idx++) {
        pretty_print_element(*l_iterator, l_idx);
      }
      break;
    }
    case kModify:
      if (m_parameters.m_note_id < l_collection.size()) {
        todo::element & l_element = l_collection[m_parameters.m_note_id];
        if (m_parameters.m_priority < 3) 
          l_element.m_priority = m_parameters.m_priority;
        if (not m_parameters.m_title.empty())
          l_element.m_title = m_parameters.m_title;
        if (not m_parameters.m_body.empty())
          l_element.m_body = m_parameters.m_body;
        if (m_parameters.m_body == "--")
          l_element.m_body.clear();
  

        pretty_print_element(l_element, m_parameters.m_note_id);
      }
      else {
        m_error = "Note out of range";
        print_usage();
        return 127;
      }
      break;
    case kInsert:
    {
      todo::element l_element(m_parameters.m_title, m_parameters.m_body);
      if (m_parameters.m_priority < 3)
        l_element.m_priority = m_parameters.m_priority;
      l_collection.push_back(l_element);
      pretty_print_element(l_element, l_collection.size() - 1);
      break;
    }
    case kDelete:
    {
      if (m_parameters.m_note_id < l_collection.size()) {
        l_collection.erase(l_collection.begin() + m_parameters.m_note_id);
        fprintf(stdout, "Note %s erased -- you now have %s notes\n",
            printColor("fgred", m_parameters.m_note_id).c_str(),
            printColor("fgcyan", l_collection.size()).c_str());
      }
      else {
        m_error = "Note out of range";
        print_usage();
        return 127;
      }
    
      break;
    }
  }

  l_collection.write_file();

  return 0;
}


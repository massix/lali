#include "element.h"
#include "application.h"
#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

using namespace todo;

application::application(int argc, char *argv[]) : 
  status(fill_parameters(argc, argv))
{

}

bool application::fill_parameters(int argc, char *argv[]) 
{
  bool l_ret(true);
  int l_index(1);

  // Sane defaults
  m_parameters.m_filling_body = false;
  m_parameters.m_todorc = std::string(getenv("HOME")) + std::string("/.todorc");
  m_parameters.m_verbose = false;
  m_parameters.m_priority = 0;
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

  if (m_action != kList and m_parameters.m_title.empty())
  {
    m_error = "Missing title for note!";
    l_ret = false;
  }

  return l_ret;
}

void application::print_usage(std::string const & p_error)
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

int application::run()
{
  if (not status) {
    print_usage();
    return 127;
  }

  switch (m_action)
  {
    case kList:
      printf("Listing\n");
      break;
    case kModify:
      printf("Modifying note %d with new priority %d new title %s and new body %s\n",
          m_parameters.m_note_id, m_parameters.m_priority, m_parameters.m_title.c_str(), m_parameters.m_body.c_str());
      break;
    case kInsert:
      printf("Inserting note with priority %d, title %s and body %s\n", 
          m_parameters.m_priority, m_parameters.m_title.c_str(), m_parameters.m_body.c_str());
      break;
    case kDelete:
      printf("Deleting note %d\n", m_parameters.m_note_id);
      break;
  }

  return 0;
}

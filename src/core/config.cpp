//
//           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                   Version 2, December 2004
//
// Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
//
// Software :
// Copyright (C) 2014 Massimo Gengarelli <massimo.gengarelli@gmail.com>
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.
//


#include "config.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace todo;

config::config(std::string const & p_filename) :
  m_config_file(p_filename)
{
  // Sane defaults
  (*this)(NOTE_COUNT_COLOR)         = "red";
  (*this)(NOTE_ID_COLOR)            = "cyan";
  (*this)(NOTE_ID_FORMAT)           = "%02d";
  (*this)(NOTE_TITLE_COLOR)         = "magenta";
  (*this)(NOTE_BODY_COLOR)          = "gray";
  (*this)(NOTE_SEARCH_COLOR)        = "yellow";
  (*this)(PRIORITY_LOW_COLOR)       = "green";
  (*this)(PRIORITY_DEFAULT_COLOR)   = "yellow";
  (*this)(PRIORITY_HIGH_COLOR)      = "red";
  (*this)(PRIORITY_LOW_TEXT)        = "low priority";
  (*this)(PRIORITY_DEFAULT_TEXT)    = "medium priority";
  (*this)(PRIORITY_HIGH_TEXT)       = "high priority";
  (*this)(ALWAYS_ASK_CONFIRMATION)  = "false";
  (*this)(MONOCHROME)               = "false";
  (*this)(PRINT_COUNTER)            = "true";
  (*this)(LIST_FORMAT)              = "   @ID@   @TITLE@@IF_BODY@ (@BODY@)@END_IF_BODY@ [@PRIORITY_TEXT@]";
  (*this)(TEMPLATES_DIRECTORY)      = "./templates/";
  (*this)(SERVER_WEB_PORT)          = "8080";
}

bool config::parse_config()
{
  bool l_ret(true);
  char l_line[1024];
  uint8_t l_index(0);

  struct stat l_stat;
  if (stat(m_config_file.c_str(), &l_stat) == -1)
    return false;

  // Open file
  std::ifstream l_file(m_config_file.c_str(), std::ifstream::in | std::ifstream::binary);

  // Read line per line
  while (not l_file.eof())
  {
    bzero(l_line, 1024);
    l_file.getline(l_line, 1024);
    if (l_line[0] == '#' or l_line[0] == ' ' or l_line[0] == '\0') continue;
    std::string l_string(l_line);

    if (l_string.substr(0, strlen(FILE_NOTES_DB)) == FILE_NOTES_DB)
    {
      (*this)(FILE_NOTES_DB) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_COUNT_COLOR)) == NOTE_COUNT_COLOR)
    {
      (*this)(NOTE_COUNT_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_ID_COLOR)) == NOTE_ID_COLOR)
    {
      (*this)(NOTE_ID_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_ID_FORMAT)) == NOTE_ID_FORMAT)
    {
      (*this)(NOTE_ID_FORMAT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_TITLE_COLOR)) == NOTE_TITLE_COLOR)
    {
      (*this)(NOTE_TITLE_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_BODY_COLOR)) == NOTE_BODY_COLOR)
    {
      (*this)(NOTE_BODY_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(NOTE_SEARCH_COLOR)) == NOTE_SEARCH_COLOR)
    {
      (*this)(NOTE_SEARCH_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_LOW_COLOR)) == PRIORITY_LOW_COLOR)
    {
      (*this)(PRIORITY_LOW_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_DEFAULT_COLOR)) == PRIORITY_DEFAULT_COLOR)
    {
      (*this)(PRIORITY_DEFAULT_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_HIGH_COLOR)) == PRIORITY_HIGH_COLOR)
    {
      (*this)(PRIORITY_HIGH_COLOR) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_LOW_TEXT)) == PRIORITY_LOW_TEXT)
    {
      (*this)(PRIORITY_LOW_TEXT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_DEFAULT_TEXT)) == PRIORITY_DEFAULT_TEXT)
    {
      (*this)(PRIORITY_DEFAULT_TEXT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRIORITY_HIGH_TEXT)) == PRIORITY_HIGH_TEXT)
    {
      (*this)(PRIORITY_HIGH_TEXT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(LIST_FORMAT)) == LIST_FORMAT)
    {
      (*this)(LIST_FORMAT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(ALWAYS_ASK_CONFIRMATION)) == ALWAYS_ASK_CONFIRMATION)
    {
      (*this)(ALWAYS_ASK_CONFIRMATION) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(PRINT_COUNTER)) == PRINT_COUNTER)
    {
      (*this)(PRINT_COUNTER) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(MONOCHROME)) == MONOCHROME)
    {
      (*this)(MONOCHROME) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(TEMPLATES_DIRECTORY)) == TEMPLATES_DIRECTORY)
    {
      (*this)(TEMPLATES_DIRECTORY) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(SERVER_WEB_PORT)) == SERVER_WEB_PORT)
    {
      (*this)(SERVER_WEB_PORT) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else
    {
      l_ret = false;
      fprintf(stderr, "Error in config file at line %d: %s\n", l_index, l_line);
      break;
    }

    l_index++;
  }

  return l_ret;
}

std::string const & config::operator[](std::string const & p_key)
{
  return const_cast<std::string const &>(std::map<std::string, std::string>::operator[](p_key));
}

std::string & config::operator()(std::string const & p_key)
{
  return std::map<std::string, std::string>::operator[](p_key);
}

uint32_t config::getServerPort()
{
  return atoi((*this)[SERVER_WEB_PORT].c_str());
}

bool config::isKeyTrue(std::string const & p_key)
{
  bool l_res(false);
  std::string const & l_ask = (*this)[p_key];
  if (l_ask == "true" or l_ask == "ok" or l_ask == "yes")
    l_res = true;

  return l_res;
}

bool config::isAskForConfirmation()
{
  return isKeyTrue(ALWAYS_ASK_CONFIRMATION);
}

bool config::isMonochrome()
{
  return isKeyTrue(MONOCHROME);
}

bool config::isCounterPrintable()
{
  return isKeyTrue(PRINT_COUNTER);
}

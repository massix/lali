#include "config.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>


using namespace todo;

config::config(std::string const & p_filename) :
  m_config_file(p_filename)
{
  // Sane defaults

  (*this)(NOTE_COUNT_COLOR)         = "red";
  (*this)(NOTE_ID_COLOR)            = "cyan";
  (*this)(NOTE_TITLE_COLOR)         = "magenta";
  (*this)(NOTE_BODY_COLOR)          = "gray";
  (*this)(NOTE_SEARCH_COLOR)        = "yellow";
  (*this)(PRIORITY_LOW_COLOR)       = "green";
  (*this)(PRIORITY_DEFAULT_COLOR)   = "yellow";
  (*this)(PRIORITY_HIGH_COLOR)      = "red";
  (*this)(ALWAYS_ASK_CONFIRMATION)  = "false";
  (*this)(MONOCHROME)               = "false";
}

bool config::parse_config()
{
  bool l_ret(true);
  char l_line[1024];
  uint8_t l_index(0);

  // Open file
  std::ifstream l_file(m_config_file.c_str(), std::ifstream::in | std::ifstream::binary);

  // Read line per line
  while (not l_file.eof())
  {
    bzero(l_line, 1024);
    l_file.getline(l_line, 1024);
    if (l_line[0] == '#' or l_line[0] == ' ' or l_line[0] == '\0') continue;
    std::string l_string(l_line);

    if (l_string.substr(0, strlen(FILE_CONFIG_FILE)) == FILE_CONFIG_FILE)
    {
      (*this)(FILE_CONFIG_FILE) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }

    else if (l_string.substr(0, strlen(FILE_NOTES_DB)) == FILE_NOTES_DB)
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
    else if (l_string.substr(0, strlen(ALWAYS_ASK_CONFIRMATION)) == ALWAYS_ASK_CONFIRMATION)
    {
      (*this)(ALWAYS_ASK_CONFIRMATION) = l_string.substr(l_string.find('=') + 2, l_string.size());
    }
    else if (l_string.substr(0, strlen(MONOCHROME)) == MONOCHROME)
    {
      (*this)(MONOCHROME) = l_string.substr(l_string.find('=') + 2, l_string.size());
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

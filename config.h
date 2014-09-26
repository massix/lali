
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>

#define NOTE_ID_COLOR           "note_id_color"
#define NOTE_TITLE_COLOR        "note_title_color"
#define NOTE_BODY_COLOR         "note_body_color"
#define PRIORITY_LOW_COLOR      "priority_low_color"
#define PRIORITY_DEFAULT_COLOR  "priority_default_color"
#define PRIORITY_HIGH_COLOR     "priority_high_color"
#define FILE_NOTES_DB           "file_notes_db"
#define FILE_CONFIG_FILE        "file_config_file"

namespace todo
{
  //// Thrown if the configuration file doesn't exist or if it is badly formatted
  //class bad_config_file : public std::runtime_exception
  //{
  //};

  class config : public std::map<std::string, std::string>
  {
    public:
      config(std::string const & p_filename);
      bool parse_config();
      std::string const & operator[](std::string const & p_key);

    private:
      std::string & operator()(std::string const & p_key);
      std::string m_config_file;
  };
}

#endif

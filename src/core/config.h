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



#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>

#define NOTE_ID_COLOR           "note_id_color"
#define NOTE_ID_FORMAT          "note_id_format"
#define NOTE_TITLE_COLOR        "note_title_color"
#define NOTE_COUNT_COLOR        "note_count_color"
#define NOTE_BODY_COLOR         "note_body_color"
#define PRIORITY_LOW_COLOR      "priority_low_color"
#define PRIORITY_DEFAULT_COLOR  "priority_default_color"
#define PRIORITY_HIGH_COLOR     "priority_high_color"
#define PRIORITY_LOW_TEXT       "priority_low_text"
#define PRIORITY_HIGH_TEXT      "priority_high_text"
#define PRIORITY_DEFAULT_TEXT   "priority_default_text"
#define NOTE_SEARCH_COLOR       "note_search_color"
#define FILE_NOTES_DB           "file_notes_db"
#define FILE_CONFIG_FILE        "file_config_file"
#define ALWAYS_ASK_CONFIRMATION "always_ask_for_confirmation"
#define MONOCHROME              "monochrome"
#define LIST_FORMAT             "list_format"

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
      bool                isAskForConfirmation();
      bool                isMonochrome();

    private:
      std::string & operator()(std::string const & p_key);
      std::string m_config_file;
      bool        isKeyTrue(std::string const & p_key);
  };
}

#endif

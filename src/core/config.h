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

#pragma once

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <list>

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
#define ALWAYS_ASK_CONFIRMATION "always_ask_for_confirmation"
#define MONOCHROME              "monochrome"
#define LIST_FORMAT             "list_format"
#define PRINT_COUNTER           "print_counter"
#define TEMPLATES_DIRECTORY     "templates_directory"
#define RESOURCES_DIRECTORY     "resources_directory"
#define SERVER_WEB_PORT         "server_web_port"
#define SERVLET_LIST            "servlet_list"

namespace todo
{

  class servlet : public std::map<std::string, std::string>
  {
    friend class config;

  public:
    typedef std::list<servlet> servlet_list;
    std::string const & operator[](std::string const & p_key) const;

  private:
    std::string & operator()(std::string const & p_key);

  };


  class config : public std::map<std::string, std::string>
  {

  public:
    config(std::string const & p_filename);
    virtual ~config();

  public:
    bool                   parse_config();
    bool                   isAskForConfirmation() const;
    bool                   isMonochrome() const;
    bool                   isCounterPrintable() const;
    uint32_t               getServerPort() const;
    servlet::servlet_list const & getServlets() const;
    std::list<std::string> getListOfServlets() const;

  public:
    std::string const & operator[](std::string const & p_key) const;

  private:
    std::string &         operator()(std::string const & p_key);
    std::string           m_config_file;
    bool                  isKeyTrue(std::string const & p_key) const;
    void                  generateServletList();
    servlet::servlet_list m_servlets;

  };
}

#endif

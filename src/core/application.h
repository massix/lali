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


#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <map>
#include "exporter.h"

namespace todo
{
class config;
class collection;

class application
{
  private:
    typedef std::map<std::string, exporter *> exporters_t;

    exporters_t m_exporters;
    std::string m_appname;
    std::string m_error;
    std::map<std::string, std::string> m_colors;
    config * m_config;
    class parameters
    {
      public:
        std::string   m_action;
        std::string   m_todorc;
        std::string   m_tododb;

        std::string   m_body;
        std::string   m_title;
        std::string   m_format;
        uint32_t      m_priority;

        uint32_t      m_note_id;

        bool          m_filling_body;
        bool          m_verbose;
        bool          m_monochrome;
        bool          m_confirmation;
        bool          m_dryrun;

        struct exporter
        {
          std::string m_file;
          std::string m_type;
        } m_exporter;
    } m_parameters;

    enum {
      kInsert,
      kDelete,
      kModify,
      kList,
      kSearch,
      kExport,
      kWeb
    } m_action;

    bool fill_parameters(int argc, char *argv[]);
    bool fill_environment();
    bool status;

    void print_usage();

    std::string print_color(std::string const & l_color,
                           std::string const & l_string,
                           bool bright = true,
                           bool underline = false);
    std::string print_color(std::string const & l_color,
                           int l_number,
                           bool bright = true,
                           bool underline = false);

    void pretty_print_element(todo::element const & p_element);

    bool ask_for_confirmation(todo::collection const & p_collection, std::string const & p_text);

  public:
    application(int argc, char *argv[]);
    virtual ~application();
    int run();
};

}

#endif

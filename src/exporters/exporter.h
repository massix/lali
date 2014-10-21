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


#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace todo
{

// Forward declarations
class element;

class exporter
{
  public:
    exporter();
    virtual ~exporter();
    bool init();
    void set_file(std::string const & p_filename);


  protected:
    virtual bool open_file();
    std::string  m_filename;
    FILE*        m_file;
    bool         m_file_is_open;


  // The following functions have to be overloaded by the exporters
  public:
    virtual bool process_note(todo::element const & p_element) = 0;
    virtual bool finalize() = 0;

  protected:
    virtual bool check_file() = 0;
    virtual bool init_checks() = 0;
};

}

#endif

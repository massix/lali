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
    exporter(std::string const & p_file);
    virtual ~exporter();
    bool init();


  protected:
    virtual bool open_file();
    std::string  m_filename;
    FILE*        m_file;
    bool         m_file_is_open;


  // The following functions have to be overloaded by the exporters
  public:
    virtual bool init_checks() = 0;
    virtual bool process_note(todo::element const & p_element) = 0;
    virtual bool finalize() = 0;

  protected:
    virtual bool check_file() = 0;
};

}

#endif

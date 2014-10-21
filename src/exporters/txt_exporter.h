#ifndef _TXT_EXPORTER_H_
#define _TXT_EXPORTER_H_

#include "exporter.h"
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace todo
{

// Forward declarations
class element;

class txt_exporter : public exporter
{
  public:
    virtual bool process_note(todo::element const & p_element);
    virtual bool finalize();

  protected:
    virtual bool check_file();
    virtual bool init_checks();
};

}

#endif

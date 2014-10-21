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

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


#include "txt_exporter.h"
#include <element/element.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace todo;

bool txt_exporter::process_note(todo::element const & p_element)
{
  char l_buffer[1024];
  snprintf(l_buffer, 1024, " %02d   --  %s  [%s]  --  %02d\n",
      p_element.m_index, p_element.m_title.c_str(), p_element.m_body.c_str(), p_element.m_priority);
  fwrite(l_buffer, strlen(l_buffer), sizeof(char), m_file);
  return true;
}

bool txt_exporter::finalize()
{
  fwrite("\n", 1, sizeof(char), m_file);
  fclose(m_file);
  m_file_is_open = false;
  return true;
}

bool txt_exporter::check_file()
{
  return true;
}

bool txt_exporter::init_checks()
{
  return true;
}

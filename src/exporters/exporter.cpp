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


#include "exporter.h"
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace todo;

exporter::exporter()
  : m_file_is_open(false)
{
}

exporter::~exporter()
{
  if (m_file_is_open)
    fclose(m_file);
}

bool exporter::init()
{
  return open_file() and init_checks();
}

bool exporter::open_file()
{
  bool l_ret(false);
  if (not m_file_is_open and not m_filename.empty()) {
    m_file = fopen(m_filename.c_str(), "w+"); 
    l_ret = (m_file not_eq NULL);
    m_file_is_open = l_ret;
  }

  return l_ret;
}

void exporter::set_file(std::string const & p_filename)
{
  m_filename = p_filename;
}

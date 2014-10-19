#include "exporter.h"
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace todo;

exporter::exporter(std::string const & p_file)
  : m_filename(p_file), m_file_is_open(false)
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

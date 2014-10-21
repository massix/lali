#include "txt_exporter.h"
#include "element.h"
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

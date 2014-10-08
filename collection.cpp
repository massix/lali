#include "collection.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace todo;

collection::collection(std::string const & p_filename) :
	m_filename(p_filename), m_sorted(0)
{
}

collection::collection() :
  m_sorted(0)
{
}

collection::~collection()
{
  if (m_sorted) delete m_sorted;
}

std::ostream & collection::serialize(std::ostream & p_stream) const
{
  const uint32_t l_separator = 0xDEADBEEF;
  uint64_t l_size = size();

  p_stream << l_size;

  std::for_each(begin(), end(), [&](todo::element const & l_element)->void {
    l_element.serialize(p_stream);
    p_stream << l_separator;
  });

  return p_stream;
}

std::istream & collection::deserialize(std::istream & p_stream)
{
  uint32_t l_separator;

  uint64_t l_size(0);
  p_stream >> l_size;

  for (uint32_t l_iter = 0; l_iter < l_size; l_iter++)
  {
    todo::element l_element;
    l_element.deserialize(p_stream);
    l_element.m_index = l_iter;
    push_back(l_element);

    p_stream >> l_separator;
  }

  return p_stream;
}

void collection::write_file() const
{
  std::ofstream l_file;

  l_file.open(m_filename.c_str(), std::ofstream::out | std::ofstream::binary);
  serialize(l_file);
  l_file.close();
}

void collection::read_file()
{
  std::ifstream l_file;

  l_file.open(m_filename.c_str(), std::ifstream::in | std::ifstream::binary);
  deserialize(l_file);
  l_file.close();
}

void collection::push_back(todo::element & p_element)
{
  p_element.m_index = size();
  if (m_sorted) {
    delete m_sorted;
    m_sorted = 0;
  }
  return std::vector<todo::element>::push_back(p_element);
}

void collection::push_back_original(todo::element const & p_element)
{
  return std::vector<todo::element>::push_back(p_element);
}

todo::collection const & collection::sort_by_priority(bool ascendent)
{
  if (m_sorted == 0)
  {
    collection l_low;
    collection l_medium;
    collection l_high;

    m_sorted = new collection();

    std::for_each(begin(), end(), [&](todo::element & l_element)->void {
      if (l_element.m_priority == 0) l_low.push_back_original(l_element);
      else if (l_element.m_priority == 1) l_medium.push_back_original(l_element);
      else l_high.push_back_original(l_element);
    });

    if (not ascendent)
      m_sorted->insert(m_sorted->end(), l_high.begin(), l_high.end());
    else
      m_sorted->insert(m_sorted->end(), l_low.begin(), l_low.end());

    m_sorted->insert(m_sorted->end(), l_medium.begin(), l_medium.end());

    if (not ascendent)
      m_sorted->insert(m_sorted->end(), l_low.begin(), l_low.end());
    else
      m_sorted->insert(m_sorted->end(), l_high.begin(), l_high.end());
  }

  return *m_sorted;
}

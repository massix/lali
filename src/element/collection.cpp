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


#include "collection.h"
#include "search.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace todo;

collection::collection(std::string const & p_filename) :
	m_filename(p_filename), m_sorted(0), m_search_result(0)
{
}

collection::collection() :
  m_sorted(0), m_search_result(0)
{
}

collection::~collection()
{
  if (m_sorted) delete m_sorted;
  if (m_search_result) delete m_search_result;
}

std::ostream & collection::serialize(std::ostream & p_stream) const
{
  const uint32_t l_separator = 0xDEADBEEF;
  uint64_t l_size = size();

  p_stream << std::ios::binary;
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

todo::collection const & collection::retrieve_notes_by_text(std::string const & l_word)
{
  std::string l_word_lowercase;
  std::for_each(l_word.begin(), l_word.end(),
      [&](const char & n)->void { l_word_lowercase.push_back(::tolower(n));
  });

  if (m_search_result == 0)
  {
    m_search_result = new collection();
    std::for_each(begin(), end(), [&](todo::element const & l_element)->void {
      std::string l_title_lowercase;
      std::for_each(l_element.m_title.begin(), l_element.m_title.end(), [&](const char & n)->void {
          l_title_lowercase.push_back(::tolower(n));
      });
      if (l_title_lowercase.find(l_word) != std::string::npos) {
        todo::element l_creation = l_element;
        l_creation.m_title = highlight_search_term(l_word, l_title_lowercase);
        m_search_result->push_back(l_creation);

        // Reset the index
        (*m_search_result)[m_search_result->size()-1].m_index = l_element.m_index;
      }
    });
  }

  return *m_search_result;
}

todo::collection const & collection::retrieve_notes_by_priority(uint32_t p_priority)
{
  if (m_search_result == 0)
  {
    m_search_result = new collection();
    std::for_each(begin(), end(), [&](todo::element const & l_element)->void{
      if (l_element.m_priority == p_priority) {
        todo::element l_creation = l_element;

        m_search_result->push_back(l_creation);
        m_search_result->back().m_index = l_element.m_index;
      }
    });
  }

  return *m_search_result;
}

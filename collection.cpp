#include "collection.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace todo;

collection::collection(std::string const & p_filename) :
	m_filename(p_filename)
{
}

collection::~collection()
{
}

std::ostream & collection::serialize(std::ostream & p_stream) const
{
	const uint32_t l_separator = 0xDEADBEEF;
	const_iterator l_iterator = begin();

	uint64_t l_size = size();

	p_stream << l_size;

	for (; l_iterator != end(); ++l_iterator) {
		l_iterator->serialize(p_stream);
		p_stream << l_separator;
	}

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
  return std::vector<todo::element>::push_back(p_element);
}


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


#include "element.h"
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace todo;

element::element() :
	m_title(), m_body(), m_priority(0), m_index(0)
{
}

element::element(std::string const & p_title) :
	m_title(p_title), m_body(), m_priority(0), m_index(0)
{
}

element::element(std::string const & p_title, std::string const & p_body) :
	m_title(p_title), m_body(p_body), m_priority(0), m_index(0)
{
}

element::~element()
{
}

std::ostream & element::serialize(std::ostream & p_stream) const
{
	p_stream << (uint8_t) 0x01;
	p_stream << m_title.size();
	p_stream << m_title;
	p_stream << (uint8_t) 0x01;
	p_stream << m_body.size();
	p_stream << m_body;
	p_stream << (uint8_t) 0x01;
	p_stream << m_priority;
	p_stream << (uint8_t) 0x01;

	return p_stream;
}

std::istream & element::deserialize(std::istream & p_stream)
{
	uint8_t l_separator;
	std::size_t l_size;

	p_stream >> l_separator;

	// Title
	p_stream >> l_size;
	if (l_separator && l_size) {
		std::vector<char> l_tmp(l_size);
		p_stream.read(&l_tmp[0], l_size);
		m_title.assign(&l_tmp[0], l_size);
	}
	
	p_stream >> l_separator;

	// Body
	p_stream >> l_size;
	if (l_separator && l_size) {
		std::vector<char> l_tmp(l_size);
		p_stream.read(&l_tmp[0], l_size);
		m_body.assign(&l_tmp[0], l_size);
	}
	p_stream >> l_separator;

	// Priority
	p_stream >> m_priority;

	p_stream >> l_separator;

	return p_stream;
}

bool element::operator==(element const & p_right) const
{
	return (
			p_right.m_title == m_title && 
			p_right.m_body == m_body &&
			p_right.m_priority == m_priority);
}


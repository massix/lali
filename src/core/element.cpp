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
#include <strings.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <cassert>

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

void element::serialize(FILE *p_file) const
{
	uint8_t  l_separator  = 0x01;
	uint32_t l_titleSize  = m_title.size();
	uint32_t l_bodySize   = m_body.size();
	uint8_t  l_priority   = (uint8_t) m_priority;

	fwrite(&l_separator,    sizeof(uint8_t),  1,           p_file);
	fwrite(&l_titleSize,    sizeof(uint32_t), 1,           p_file);
	fwrite(m_title.c_str(), sizeof(char),     l_titleSize, p_file);
	fwrite(&l_separator,    sizeof(uint8_t),  1,           p_file);
	fwrite(&l_bodySize,     sizeof(uint32_t), 1,           p_file);
	fwrite(m_body.c_str(),  sizeof(char),     l_bodySize,  p_file);
	fwrite(&l_separator,    sizeof(uint8_t),  1,           p_file);
	fwrite(&l_priority,     sizeof(uint8_t),  1,           p_file);
}

void element::deserialize(FILE *p_file)
{
  uint8_t  const l_separator(0x01);
  uint32_t       l_titleSize(0);
  uint32_t       l_bodySize(0);
  uint8_t        l_priority(0);
	char *         l_buffer;

	fread((void *) &l_separator, sizeof(uint8_t), 1, p_file);
	assert(l_separator == 0x01);

	fread((void *) &l_titleSize, sizeof(uint32_t), 1, p_file);
	assert(l_titleSize > 0);

	l_buffer = new char[l_titleSize];
	bzero(l_buffer, l_titleSize);
	fread((void *) l_buffer, sizeof(char), l_titleSize, p_file);
	l_buffer[l_titleSize] = '\0';

	m_title.assign(l_buffer);
	delete [] l_buffer;

	fread((void *) &l_separator, sizeof(uint8_t), 1, p_file);
	assert(l_separator == 0x01);

	fread((void *) &l_bodySize, sizeof(uint32_t), 1, p_file);

	if (l_bodySize) {
			l_buffer = new char[l_bodySize];
			bzero(l_buffer, l_bodySize);
			fread((void *) l_buffer, sizeof(char), l_bodySize, p_file);
			l_buffer[l_bodySize] = '\0';
			m_body.assign(l_buffer);
			delete [] l_buffer;
	}

	fread((void *) &l_separator, sizeof(uint8_t), 1, p_file);
	assert(l_separator == 0x01);

	fread((void *) &l_priority, sizeof(uint8_t), 1, p_file);
	m_priority = l_priority;
}

bool element::operator==(element const & p_right) const
{
	return (
			p_right.m_title == m_title &&
			p_right.m_body == m_body &&
			p_right.m_priority == m_priority);
}


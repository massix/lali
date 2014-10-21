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


#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>

namespace todo
{
class element
{
	public:
		element();
		element(std::string const & p_title);
		element(std::string const & p_title, std::string const & p_body);

		virtual ~element();

		bool operator==(element const & p_right) const;

		std::ostream & serialize   (std::ostream & p_stream) const;
		std::istream & deserialize (std::istream & p_stream);

		std::string  m_title;
		std::string  m_body;
		uint8_t      m_priority;
    uint32_t     m_index;
};

}

#endif

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

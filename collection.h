#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "element.h"
#include <vector>

namespace todo
{
class collection : public std::vector<todo::element>
{
	public:
		collection(std::string const & p_filename);

		virtual ~collection();

		std::ostream & serialize   (std::ostream & p_stream) const;
		std::istream & deserialize (std::istream & p_stream);

    void write_file() const;
    void read_file();

	private:
		std::string m_filename;
};

}

#endif

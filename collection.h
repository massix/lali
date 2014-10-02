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
    virtual void push_back(todo::element & p_element);

		std::ostream & serialize   (std::ostream & p_stream) const;
		std::istream & deserialize (std::istream & p_stream);

    void write_file() const;
    void read_file();

    collection const & sort_by_priority();

    uint32_t get_longest_string() const;
  protected:
    collection();
    void push_back_original(todo::element const & p_element);

	private:
		std::string   m_filename;
    collection *  m_sorted;
    uint32_t      m_longest_string;
};

}

#endif

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

    collection const & sort_by_priority(bool ascendent = false);
    collection const & retrieve_notes_by_text(std::string const & l_word);
  protected:
    collection();
    void push_back_original(todo::element const & p_element);

	private:
		std::string   m_filename;
    collection *  m_sorted;
    collection *  m_search_result;
};

}

#endif

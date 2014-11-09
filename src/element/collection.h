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


#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "element.h"
#include <vector>

#ifndef __TESTABLE__
#define __TESTABLE__ private
#endif

namespace todo
{
    class collection : public std::vector<todo::element>
    {
    public:
        collection(std::string const & p_filename);

        virtual ~collection();
        virtual void push_back(todo::element & p_element);

        void write_file() const;
        void read_file();

        collection const & sort_by_priority(bool ascendent = false);
        collection const & retrieve_notes_by_text(std::string const & l_word);
        collection const & retrieve_notes_by_priority(uint32_t p_priority);
    protected:
        collection();
        void           serialize   (FILE* p_file) const;
        void         deserialize   (FILE* p_file);

        void push_back_original(todo::element const & p_element);

    private:
        std::string   m_filename;
        collection *  m_sorted;
        collection *  m_search_result;

    __TESTABLE__:
        void unlink();
    };

}

#endif

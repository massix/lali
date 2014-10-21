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


#include "search.h"

std::string todo::highlight_search_term(std::string const & p_search_term, std::string const & p_text)
{
  auto l_result = p_text;

  auto l_pos = l_result.find(p_search_term);
  if (l_pos != std::string::npos)
  {
    l_result.insert(l_pos + p_search_term.size(), "$END$");
    l_result.insert(l_pos, "$BEGIN$");
  }

  return l_result;
}


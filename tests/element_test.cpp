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
#include "search.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

void bug_numbers_at_beginning()
{
  todo::element l_element;
  todo::element l_different;

  l_element.m_title = "30 nota";
}

int main()
{
	todo::element l_element;
	todo::element l_different;

	l_element.m_title = "First title";
  l_element.m_body  = "Element body with a searchable term";

  FILE * l_test = fopen("temp.bin", "w+");
  l_element.serialize(l_test);
  rewind(l_test);

  l_different.deserialize(l_test);
  fclose(l_test);

  std::string l_search_result = todo::highlight_search_term("search", l_different.m_body);
  assert(l_search_result == "Element body with a $BEGIN$search$END$able term");

  bug_numbers_at_beginning();

	return 0;
}

#include "element.h"
#include "search.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main()
{
	todo::element l_element;
	todo::element l_different;

	l_element.m_title = "First title";
	l_element.m_body  = "Element body with a searchable term";

	std::stringstream l_stream;
	l_element.serialize(l_stream);
	l_different.deserialize(l_stream);

	assert(l_different == l_element);

  std::string l_search_result = todo::highlight_search_term("search", l_different.m_body);
  assert (l_search_result == "Element body with a $BEGIN$search$END$able term");
	return 0;
}


#include "element.h"
#include "collection.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main()
{
	todo::collection l_collection("./test.bin");
	todo::collection l_other_collection("./test.bin");

	for (uint32_t l_i = 0; l_i < 1 << 14; l_i++) {
		todo::element l_elem("Yoo", "Yee");
		l_collection.push_back(l_elem);
	}

  todo::element l_elem("note with searchable text", "and a body");
  l_collection.push_back(l_elem);

	std::stringstream l_stream;
	l_collection.serialize(l_stream);
	l_other_collection.deserialize(l_stream);

	assert(l_collection == l_other_collection);

  todo::collection l_result = l_other_collection.retrieve_notes_by_text("search");
  assert(l_result.size() == 1);
  assert(l_result[0].m_title == "note with $BEGIN$search$END$able text");

	return 0;
}

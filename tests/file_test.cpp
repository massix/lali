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

  l_collection.write_file();
  l_other_collection.read_file();

  assert(l_collection == l_other_collection);
	return 0;
}


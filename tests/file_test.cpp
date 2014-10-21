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


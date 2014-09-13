#include "element.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main()
{
	todo::element l_element;
	todo::element l_different;

	l_element.m_title = "First";
	l_element.m_body  = "Element";

	std::stringstream l_stream;
	l_element.serialize(l_stream);
	l_different.deserialize(l_stream);

	assert(l_different == l_element);
	return 0;
}


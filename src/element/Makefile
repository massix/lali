include ../../Include.make
CXXFLAGS = -Wall -Wextra -g -O0 -DTODO_VERSION=\"${VERSION}\" -std=c++11 -I../core -I../exporters -I.
PREFIX   = /usr/local

compiled_OBJECTS = collection.o element.o
compiled_LIBRARY = libelement.a


all: $(compiled_LIBRARY)

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $?

${compiled_LIBRARY}: ${compiled_OBJECTS}
	$(AR) rcs ${compiled_LIBRARY} ${compiled_OBJECTS}

clean:
	rm -f ${compiled_OBJECTS} ${compiled_LIBRARY}


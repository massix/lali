CXX      = g++
CXXFLAGS = -Wall -Wextra -g -O0

BINARIES = element_test
OBJECTS  = element.o element_test.o main.o

element_OBJECTS = element.o
collection_OBJECTS = collection.o

element_test_OBJECTS = element_test.o
element_test_BINARY  = element_tu

collection_test_OBJECTS = collection_test.o
collection_test_BINARY = collection_tu

all: $(element_test_BINARY) $(collection_test_BINARY)

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -c -o $@ $?

$(element_test_BINARY): $(element_OBJECTS) $(element_test_OBJECTS)
	$(CXX) -o $@ $+

$(collection_test_BINARY): $(collection_OBJECTS) $(element_OBJECTS) $(collection_test_OBJECTS)
	$(CXX) -o $@ $+

check: $(collection_test_BINARY) $(element_test_BINARY)
	./$(element_test_BINARY)
	./$(collection_test_BINARY)
	
clean: 
	rm -f *.o *.bin $(collection_test_BINARY) $(element_test_BINARY)


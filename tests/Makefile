include ../Include.make
CXXFLAGS = -Wall -Wextra -g -O0 -DTODO_VERSION=\"${VERSION}\" -std=c++11 -I../src/element -I../src/exporters -I../src/core
LDFLAGS  = -L../src/core -L../src/element -L../src/exporters -lelement -lexporter -lcore
PREFIX   = /usr/local

collection_test = collection_tu
config_test = config_tu
element_test = element_tu
file_test = file_tu

all: ${collection_test} ${config_test} ${file_test} ${element_test}

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $?

${collection_test}: collection_test.o
	$(CXX) $? ${LDFLAGS} -o $@  

${config_test}: config_test.o
	$(CXX) $? ${LDFLAGS} -o $@  

${element_test}: element_test.o
	$(CXX) $? ${LDFLAGS} -o $@  

${file_test}: file_test.o
	$(CXX) $? ${LDFLAGS} -o $@  
	
check: ${collection_test} ${config_test} ${file_test} ${element_test}
	./${collection_test}
	./${config_test}
	./${file_test}
	./${element_test}

clean:
	rm -f *.o ${collection_test} ${config_test} ${element_test} ${file_test}


VERSION  = 0.2.1
CXX      = g++
CXXFLAGS = -Wall -Wextra -g -O0 -DTODO_VERSION=\"${VERSION}\"

element_OBJECTS = element.o
collection_OBJECTS = collection.o
config_OBJECTS = config.o

element_test_OBJECTS = element_test.o
element_test_BINARY  = element_tu

collection_test_OBJECTS = collection_test.o
collection_test_BINARY = collection_tu

file_test_BINARY = file_tu
file_test_OBJECTS = file_test.o

config_test_BINARY = config_tu
config_test_OBJECTS = config_test.o

main_OBJECTS = main.o application.o
main_BINARY = todo

all: $(main_BINARY) $(element_test_BINARY) $(collection_test_BINARY) $(file_test_BINARY) $(config_test_BINARY)

.cpp.o: %.cpp
	@$(CXX) $(CXXFLAGS) -I. -c -o $@ $?
	@echo "CXX $?"

$(config_test_BINARY): $(config_OBJECTS) $(config_test_OBJECTS)
	@$(CXX) -o $@ $+
	@echo "LD $@ -- ${VERSION}"

$(element_test_BINARY): $(element_OBJECTS) $(element_test_OBJECTS)
	@$(CXX) -o $@ $+
	@echo "LD $@ -- ${VERSION}"

$(collection_test_BINARY): $(collection_OBJECTS) $(element_OBJECTS) $(collection_test_OBJECTS)
	@$(CXX) -o $@ $+
	@echo "LD $@ -- ${VERSION}"

$(file_test_BINARY): $(collection_OBJECTS) $(element_OBJECTS) $(file_test_OBJECTS)
	@$(CXX) -o $@ $+
	@echo "LD $@ -- ${VERSION}"

$(main_BINARY): $(collection_OBJECTS) $(element_OBJECTS) $(config_OBJECTS) $(main_OBJECTS)
	@$(CXX) -o $@ $+
	@echo "LD $@ -- ${VERSION}"

check: $(collection_test_BINARY) $(element_test_BINARY) $(file_test_BINARY) $(config_test_BINARY)
	@echo "Checking $(element_test_BINARY)"
	@./$(element_test_BINARY)
	@echo "Checking $(collection_test_BINARY)"
	@./$(collection_test_BINARY)
	@echo "Checking $(file_test_BINARY)"
	@./$(file_test_BINARY)
	@echo "Checking $(config_test_BINARY)"
	@./$(config_test_BINARY)

clean:
	@echo "Clean"
	@rm -f *.o *.bin $(collection_test_BINARY) $(element_test_BINARY) $(file_test_BINARY) $(main_BINARY) $(config_test_BINARY)

VERSION  = 0.3.1
CXX      = g++
CXXFLAGS = -Wall -Wextra -g -O0 -DTODO_VERSION=\"${VERSION}\" -std=c++11
PREFIX   = /usr/local

element_OBJECTS = element.o
collection_OBJECTS = collection.o
config_OBJECTS = config.o

element_test_OBJECTS = element_test.o search.o
element_test_BINARY  = element_tu

collection_test_OBJECTS = collection_test.o search.o
collection_test_BINARY = collection_tu

file_test_OBJECTS = file_test.o search.o
file_test_BINARY = file_tu

config_test_BINARY = config_tu
config_test_OBJECTS = config_test.o

main_OBJECTS = main.o application.o search.o exporter.o txt_exporter.o
main_BINARY = hali

all: $(main_BINARY)

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

install: $(main_BINARY)
	@echo "Installing in ${PREFIX}"
	@/usr/bin/install -m 0755 $(main_BINARY) ${PREFIX}/bin/${main_BINARY}

remove:
	@echo "Removing from ${PREFIX}"
	@rm -f ${PREFIX}/bin/${main_BINARY}

clean:
	@echo "Clean"
	@rm -f *.o *.bin $(collection_test_BINARY) $(element_test_BINARY) $(file_test_BINARY) $(main_BINARY) $(config_test_BINARY)

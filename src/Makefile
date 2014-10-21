include ../Include.make
SUBDIRS = core element exporters
TARGET  = hali
target_OBJECTS = main.o
CXXFLAGS = -Wall -Wextra -g -O0 -DTODO_VERSION=\"${VERSION}\" -std=c++11 -Ielement -Iexporters -Icore
LDFLAGS  = -Lcore -lcore -Lelement -lelement -Lexporters -lexporter

.PHONY: core element exporters

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $?

all:
	@for d in ${SUBDIRS}; do $(MAKE) -C $$d; done

clean:
	@for d in ${SUBDIRS}; do $(MAKE) clean -C $$d; done
	rm -f ${TARGET} *.o

check:
	@for d in ${SUBDIRS}; do $(MAKE) check -C $$d; done

${TARGET}: all main.o
	$(CXX) main.o core/*.o element/*.o exporters/*.o ${LDFLAGS} -o $@ 


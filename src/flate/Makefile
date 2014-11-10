CXX	= clang++
CFLAGS	= -Wall
AR	= ar -r
RM	= rm -f

all:	libflate

libflate: flate.o
	$(AR) libflate.a flate.o

flate.o: flate.c
	$(CXX) $(CFLAGS) flate.c -c -I.

clean:
	$(RM) flate.o libflate.a

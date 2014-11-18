AM_CXXFLAGS = -std=c++11 -I$(abs_top_srcdir)/src/
LDADD = $(top_srcdir)/src/core/libcore.a

noinst_PROGRAMS = collection_test_tu config_test_tu element_test_tu file_test_tu
collection_test_tu_SOURCES = collection_test.cpp
config_test_tu_SOURCES = config_test.cpp
element_test_tu_SOURCES = element_test.cpp
file_test_tu_SOURCES = file_test.cpp


test_all:
	./collection_test_tu
	./config_test_tu
	./element_test_tu
	./file_test_tu

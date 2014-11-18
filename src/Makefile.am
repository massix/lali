SUBDIRS = core exporters flate web
AM_CXXFLAGS = -std=c++0x -DPACKAGE_VERSION=\"${PACKAGE_VERSION}\"
bin_PROGRAMS = lali

lali_SOURCES = main.cpp
lali_LDADD = core/libcore.a exporters/libexporters.a web/libweb.a flate/libflate.a

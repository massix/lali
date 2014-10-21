include ./Include.make
SUBDIRS  = src

.PHONY: src clean check

all: src hali

src:
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C tests

check: src
	$(MAKE) check -C tests

hali: src
	$(MAKE) hali -C src

install: hali
	@echo "Installing in ${PREFIX}"
	@/usr/bin/install -m 0755 src/hali ${PREFIX}/bin/hali
	@echo "Do not forget to copy ./config_file.example.todo to ${HOME}/.halirc"

remove:
	@echo "Removing from ${PREFIX}"
	@rm -f ${PREFIX}/bin/hali

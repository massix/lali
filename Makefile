include ./Include.make
SUBDIRS  = src

.PHONY: src clean check

all: src lali

src:
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C tests

check: src
	$(MAKE) check -C tests

lali: src
	$(MAKE) lali -C src

install: lali
	@echo "Installing in ${PREFIX}"
	@/usr/bin/install -m 0755 src/lali ${PREFIX}/bin/lali
	@echo "Do not forget to copy ./config_file.example.todo to ${HOME}/.lalirc"

remove:
	@echo "Removing from ${PREFIX}"
	@rm -f ${PREFIX}/bin/lali

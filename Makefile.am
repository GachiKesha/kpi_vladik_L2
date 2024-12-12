AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = donk
donk_SOURCES = main.cpp donk.h
dist_man_MANS = donk.1
CXXFLAGS = -g -Wall 
CLEANFILES = *.o *.gch

CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

.PHONY: deb
deb:	
	mkdir -p $(CTRLF_DIR)
	echo Package: $(PACKAGE) > $(CTRLF_NAME)
	echo Version: $(VERSION) >> $(CTRLF_NAME)
	echo Architecture: all >> $(CTRLF_NAME)
	echo Maintainer: $(PACKAGE_BUGREPORT) >> $(CTRLF_NAME)
	echo -n "Description:" >> $(CTRLF_NAME)
	cat donk.1 >> $(CTRLF_NAME)
	make DESTDIR=$(CURDIR)/deb install
	

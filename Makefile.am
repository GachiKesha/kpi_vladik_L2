AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = donk
donk_SOURCES = main.cpp donk.h
CXXFLAGS = -g -Wall 
CLEANFILES = *.o *.gch

uninstall-hook:
	rm -d $(datarootdir)/$(PACKAGE)/data
	rm -d $(datarootdir)/$(PACKAGE)
	
CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

.PHONY: deb debug
debug:
    $(foreach v, $(.VARIABLES), $(info $(v)=$($(v))))

deb:
    mkdir -p $(CTRL_DIR)
    echo Package: $(PACKAGE) > $(CTRLF_NAME)
    echo Version: $(VERSION) >> $(CTRLF_NAME)
    echo Architecture: all >> $(CTRLF_NAME)
    echo Maintainer: $(PACKAGE_BUGREPORT) >> $(CTRLF_NAME)
    echo -n "Description: " >> $(CTRLF_NAME)
    cat pkg_descr >> $(CTRLF_NAME)
    make DESTDIR=$(CURDIR)/deb install


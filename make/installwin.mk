DEST=$(INSTALL_DIR)/$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
IMPORT_LIB_NAME := $(call libname,qpdf)
installwin: all
	$(RM) -r $(INSTALL_DIR)
	mkdir $(INSTALL_DIR)
	mkdir $(DEST)
	mkdir $(DEST)/bin
	mkdir $(DEST)/lib
	mkdir $(DEST)/include
	mkdir $(DEST)/include/qpdf
	mkdir $(DEST)/doc
	cp libqpdf/$(OUTPUT_DIR)/$(IMPORT_LIB_NAME) $(DEST)/lib
	cp libqpdf/$(OUTPUT_DIR)/qpdf*.dll $(DEST)/bin
	perl copy_dlls libqpdf/$(OUTPUT_DIR)/qpdf*.dll $(DEST)/bin $(OBJDUMP) $(WINDOWS_WORDSIZE)
	cp qpdf/$(OUTPUT_DIR)/qpdf.exe $(DEST)/bin
	cp zlib-flate/$(OUTPUT_DIR)/zlib-flate.exe $(DEST)/bin
	cp qpdf/$(OUTPUT_DIR)/fix-qdf.exe $(DEST)/bin
	cp include/qpdf/*.h $(DEST)/include/qpdf
	cp include/qpdf/*.hh $(DEST)/include/qpdf
	if [ -f doc/qpdf-manual.html ]; then \
	    mkdir $(DEST)/doc/_static; \
	    cp doc/qpdf-manual.html $(DEST)/doc; \
	    cp doc/_static/* $(DEST)/doc/_static; \
	fi
	if [ -f doc/qpdf-manual.pdf ]; then \
	    cp doc/qpdf-manual.pdf $(DEST)/doc; \
	fi

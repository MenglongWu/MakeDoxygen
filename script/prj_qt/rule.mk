
MOC_DIR=/opt/qt-4.7.3/bin/

# ifeq ("$(ARCH)", "arm926")
# 	MOC_DIR=
# endif
# ifeq ("$(ARCH)", "win32")
#	MOC_DIR=
# endif

MOC= $(MOC_DIR)moc



moc:$(MOCS-y)
	@echo 
%.moc.cpp:%.h
	@echo -e $(CYAN)"    moc    $@"$(NORMAL)
	@$(MOC)    $^ > $@

rmmoc:
	@rm -rf $(MOCS-y)	



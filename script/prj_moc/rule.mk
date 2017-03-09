
MOC=/opt/qt-4.7.3/bin/moc


moc:$(MOCS-y)
	@echo 
%.moc.cpp:%.h
	@echo -e $(CYAN)"    moc        $@"$(NORMAL)
	@$(MOC)    $^ > $@

rmmoc:
	@rm -rf $(MOCS-y)	



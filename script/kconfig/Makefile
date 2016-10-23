# ===========================================================================
# Kernel configuration targets
# These targets are used from top-level makefile
SHELL=/bin/bash

PHONY += oldconfig xconfig gconfig menuconfig config silentoldconfig update-po-config


#################################################################
NORMAL = "\e[0;1m"
BLACK = "\e[30;1m"
RED  =  "\e[31;1m"
GREEN = "\e[32;1m"
YELLOW = "\e[33;1m"
BLUE  = "\e[34;1m"
PURPLE = "\e[35;1m"
CYAN  = "\e[36;1m"
WHITE = "\e[37;1m"

obj= mconf.o \
	zconf.tab.o \
	lxdialog/checklist.o \
	lxdialog/util.o \
	lxdialog/inputbox.o \
	lxdialog/textbox.o \
	lxdialog/yesno.o \
	lxdialog/menubox.o

all:$(obj)
	@gcc      $(obj) -o mconf -Ilxdialog -lncurses

%.o:%.c
	@echo -e $(CYAN)"    compile    $^"  $(NORMAL)
	@$(CC) -o $@ -c $^ -Ilxdialog -lncurses

clean:
	@-rm -f $(obj)
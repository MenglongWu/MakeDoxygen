
PRJ_NAME       = "[default-project]"
PRJ_VERSION    = 1
PRJ_PATCHLEVEL = 0
PRJ_SUBLEVEL   = 0


# default download.elf,download.dis,download.bin
OUTPUT_ELF	= mconf



INCLUDE_DIR	+= -I./script/kconfig/lxdialog -I./script/kconfig
LFLAGS		+= -lncurses
LIB_DIR 	+= 
CFLAGS  += 



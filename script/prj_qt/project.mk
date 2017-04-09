# insert common config
#
include script/qt-common/qt.mk


# the subproject private config 
#
PRJ_VERSION = "1.0.0"
PRJ_NAME = "qttest"

# default download.elf,download.dis,download.bin
OUTPUT_ELF	= qt-hello.elf
# OUTPUT_DIS	=
# OUTPUT_BIN	= 
# OUTPUT_SO 	= 
# OUTPUT_A	=
OUTPUT_DIR = release


INCLUDE_DIR	+= $(GCHS_INCLUDE_DIR)
LFLAGS		+= 
LIB_DIR 	+= 
CFLAGS  	+=



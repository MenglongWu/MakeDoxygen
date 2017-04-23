# insert common config
#
include script/qt-common/qt.mk


# the subproject private config 
#
PRJ_VERSION = "1.0.0"
PRJ_NAME = "qttest"

# default download.elf,download.dis,download.bin
OUTPUT_ELF	= qt-moc.elf
# OUTPUT_DIS	=
# OUTPUT_BIN	= 
# OUTPUT_SO 	= 
# OUTPUT_A	=
OUTPUT_DIR 	= release


# only a Qt example 
#

# 'GCHS_INCLUDE_DIR' is different to 'INCLUDE_DIR', 'GCHS_INCLUDE_DIR' only for
# precompile
#
INCLUDE_DIR	+= -I./src -I./src/qt $(GCHS_INCLUDE_DIR)
LFLAGS		+=
LIB_DIR 	+=
CFLAGS  	+=



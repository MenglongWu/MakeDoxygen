#
# Makefile Template for "Application Program"
#
# Description:
#	Automatic load file config list "config_xxx_file_list.mk"
#	which will be complie,when use this Makefile Template,
#	you only edit the config_xxx_file_list.mk
#
#
# Author: Menglong Wu
# E-mail:DreagonWoo@163.com
#
#
# V0.1		2014-08-23
#		2 demo makefile AppMakefile.mk and LibMakefile.mk
# V0.2		2015-08-21
#	- load file_list
#	- load output



export TOP_DIR = $(realpath ./)

include script/listprj.mk
ifeq ("$(file_common)", "")
	ifeq ($(TOP_DIR)/script/common.mk, $(wildcard $(TOP_DIR)/script/common.mk))
		file_common = $(TOP_DIR)/script/common.mk
		include $(TOP_DIR)/script/common.mk
	else
		file_common = ========== no such file ./script/common.mk 
	endif
else
	include $(common)
endif
#################################################################
# load default project configure: script/project.mk
ifeq ("$(file_prj)", "")
	ifeq ($(TOP_DIR)/script/project.mk, $(wildcard $(TOP_DIR)/script/project.mk))
		file_prj = $(TOP_DIR)/script/project.mk
		include $(TOP_DIR)/script/project.mk
	else
		project = ========== no such file ./script/project.mk 
	endif
else
	include $(file_prj)
endif
# include $(file_prj)

#################################################################
# CROSS_COMPILE		- While the cross tool link
# ARCH				- Target platform
# ARCH=x86
# DEV=MCU
# ifeq ("$(ARCH)", "")
# 	ARCH=x86
# endif

# ifeq ("$(ARCH)", "arm920t")
# 	CROSS_COMPILE	=/opt/EmbedSky/crosstools_3.4.5_softfloat/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-
# endif

# ifeq ("$(ARCH)", "armv7")
# 	CROSS_COMPILE	=/opt/iTop-4412/4.3.2/bin/arm-linux-
# endif

# ifeq ("$(ARCH)", "i586")
# 	CROSS_COMPILE	=i586-mingw32msvc-
# endif

# ifeq ("$(DEV)", "")
# 	DEV=MCU
# endif

# ifeq ("$(DEV)", "M")
# 	CFLAGS =-D_MANAGE
# endif


#################################################################
# select which file be complie,it edit in config_app_file.mk
# Import all files,it edit in config_xxx_file_list.mk
ifeq ("$(file_config)", "")
	ifeq ($(TOP_DIR)/script/config.mk, $(wildcard $(TOP_DIR)/script/config.mk))
		file_config = ./script/config.mk
		include $(file_config)
	else
		file_config = ========== no such file ./script/config.mk
	endif
else
	include $(file_config)
endif



ifeq ("$(file_list)", "")
	ifeq ($(TOP_DIR)/script/default/filelist.mk, $(wildcard $(TOP_DIR)/script/default/filelist.mk))
		file_list = $(TOP_DIR)/script/default/filelist.mk
		include $(file_list)
	else
		file_list = ========== no such file ./script/default/filelist.mk 
	endif
else
	include $(file_list)
endif

ifeq ("$(file_lds)", "")
	ifeq ($(TOP_DIR)/script/default/boot.lds, $(wildcard $(TOP_DIR)/script/default/boot.lds))
		file_lds = $(TOP_DIR)/script/default/boot.lds
		# include $(file_lds)
	else
		file_lds = ========== no such file ./script/default/boot.lds 
	endif
else
	include $(file_list)
endif


#################################################################
OBJS = 	$(patsubst %.S,%.o,\
		$(patsubst %.cpp,%.o,\
		$(patsubst %.c,%.o,$(SRCS-y))))

#################################################################
# Output files name and directory
# 

ifeq ("$(OUTPUT_ELF)", "")
	OUTPUT_ELF	= download.elf
endif
ifeq ("$(OUTPUT_DIS)", "")
	OUTPUT_DIS	= download.dis
endif
ifeq ("$(OUTPUT_BIN)", "")
	OUTPUT_BIN	= download.bin
endif
ifeq ("$(OUTPUT_SO)", "")
	OUTPUT_SO	= download.so
endif
ifeq ("$(OUTPUT_A)", "")
	OUTPUT_A	= download.a
endif
ifeq ("$(OUTPUT_DIR)", "")
	OUTPUT_DIR	= release
endif

MAKE_DIR	+= include doxygen




#################################################################
# macro NOWTIME "yyyy-mm-dd_HH:MM:SS"
NOWTIME="$(shell date "+%Y-%m-%d_%H:%M:%S")"

#################################################################
# INCLUDE_DIR	- Where will be search *.h file
# LFLAGS		- Linking option
# LIB_DIR		- Where will be search *.so/*.a file
#-Wl,-rpath=./:./lib/

#when app.elf run will select *.so/a from $(PATH) -> ./ -> ./lib/
# INCLUDE_DIR += 
# LFLAGS	    += 
# LIB_DIR     += 
CFLAGS      += -DBUILD_DATE=\"$(NOWTIME)\"  -DPRJ_VERSION=\"$(PRJ_VERSION)\" -DPRJ_NAME=\"$(PRJ_NAME)\"


#################################################################
GCC_G++ = gcc
CC 	= $(CROSS_COMPILE)$(GCC_G++)
LD 	= $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

#################################################################
# CFLAGS		- Compile general option
# CC_FLAGS		- Compile only for *.c file option
# CS_FLAGS		- Compile only for *.S file option
CFLAGS		+= -g  	 -Wall -static -rdynamic
ifeq ("$(GCC_G++)","gcc") # only compile gcc use -std=gnu99 option
	CC_FLAGS    = -std=gnu99
else
	CC_FLAGS    = 
endif



CC_FLAGS   += $(CFLAGS)
CS_FLAGS   += $(CFLAGS)

ifeq ("$(load_lds)","y") 
	load_lds = load_lds-y
else
	load_lds = load_lds-n
endif



all:echo-arch elf bin dis

configure: init_dir
	echo $(file_config) include/autoconfig.h $(PRJ_NAME)
	@mkheader $(file_config) include/autoconfig.h $(PRJ_NAME)

# list all project
lp:
	@cat script/listprj.mk | grep ".mk" | grep -v "#"

# 
dis:echo-arch elf
	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_DIS)"
	@$(OBJDUMP) -S $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) > $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_DIS)	

# create bin file, for system on chip without operating system
bin:echo-arch elf
	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_BIN)"
	@$(OBJCOPY) -O binary -S $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_BIN)
#################################################################
# it's a ELF application program file on linux,*.lds is auto loaded 
# by system from default path
elf:echo-arch $(load_lds)

load_lds-n:$(OUTPUT_DIR)-$(ARCH) $(OBJS)
	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF)"
	@$(CC) -o $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) $(OBJS) $(LIB_DIR) $(LFLAGS)

# it's a bootloader bin file,user have to select *.lds file by your self
# default file_lds = boot.lds
load_lds-y:$(OUTPUT_DIR)-$(ARCH) $(OBJS)

	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF)"
	@$(LD) -T$(file_lds) $(OBJS) -o $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) $(LFLAGS) $(LIB_DIR)  
#################################################################
.PHONY: mlib
mlib:echo-arch  $(OUTPUT_DIR)-$(ARCH) $(OBJS)
	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_SO)"
	@$(CC) -shared -fPIC -o $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_SO) $(OBJS)
	@echo "    create     $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_A)"
	@ar rcs $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_A) $(OBJS)
#################################################################
echo-arch:
	@echo "    ARCH       [$(ARCH)]"
%.o:%.c
	@echo "    compile    $^"
	@$(CC) -o $@ -c $^ $(CC_FLAGS) $(INCLUDE_DIR)
%.o:%.cpp
	@echo "    compile    $^"
	@$(CC) -o $@ -c $^ $(CC_FLAGS) $(INCLUDE_DIR) 
%.o:%.S
	@echo "    compile    $^"
	@$(CC) -o $@ -c $^ $(CS_FLAGS) $(INCLUDE_DIR)



#################################################################
# make directory
$(OUTPUT_DIR)-$(ARCH):
	@mkdir $(OUTPUT_DIR)-$(ARCH)

# .PHONY:$(MAKE_DIR)
init_dir:$(MAKE_DIR)
	
$(MAKE_DIR):
	@mkdir $@


#################################################################
.PHONY: clean
clean:
	@-rm -f $(OBJS)  \
		$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_DIS) \
		$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) \
		$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_BIN) \
		$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_SO) \
		$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_A)
	@-rm -f core

.PHONY: disclean
disclean:clean
	@-rm $(OUTPUT_DIR)-$(ARCH) -rf
#################################################################


run:
	./$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF)

gdb:
	gdb ./$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF)
gdb-core:
	gdb ./$(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) core


print_env:
	@echo =========================================================
	echo $(VAR)
	@echo PRJ_VERSION "  "= $(PRJ_VERSION)
	@echo PRJ_NAME "     "= $(PRJ_NAME)

	@echo 
	@echo file_common "  "= $(file_common)
	@echo file_prj "     "= $(file_prj)
	@echo file_config "  "= $(file_config)
	@echo file_list "    "= $(file_list)
	@echo file_lds "     "= $(file_lds)

	@echo 
	@echo CROSS_COMPILE = $(CROSS_COMPILE)
	@echo CC "           "= $(CC)
	@echo LD "           "= $(LD)
	@echo OBJDUMP "      "= $(OBJDUMP)
	@echo OBJCOPY "      "= $(OBJCOPY)

	@echo 
	@echo OUTPUT_ELF "   "= $(OUTPUT_ELF)
	@echo OUTPUT_DIS "   "= $(OUTPUT_DIS)
	@echo OUTPUT_BIN "   "= $(OUTPUT_BIN)
	@echo OUTPUT_SO "    "= $(OUTPUT_SO)
	@echo OUTPUT_A "     "= $(OUTPUT_A)
	@echo OUTPUT_DIR "   "= $(OUTPUT_DIR)

	@echo 
	@echo INCLUDE_DIR " " = $(INCLUDE_DIR)
	@echo LFLAGS "      " = $(LFLAGS)
	@echo LIB_DIR "     " = $(LIB_DIR)
	@echo CFLAGS "      " = $(CFLAGS)

	@echo $(SRCS-y)
help:
	@echo ======================== Makefile help ========================
	@echo "    "configure"    "make autoconfig.h from config file default config.mk
	@echo "    "all"          "create *.elf,*.bin

	@echo "    "clean"        "clean output file depend on *.o and OUTPUT_xxx\(OUTPUT_ELF and so on\)
	@echo "    "lp"           "list project
	@echo "    "library"      "create *.so, *.a
	@echo "    "print_env"    "display environment,only for debug Makefile
	@echo "    "run"          "run *elf 
	@echo "    "gdb"          "gdb debug
	@echo "    "gdb-core"     "gdb debug and load core
	@echo 
	@echo "Environment"
	@echo "    "CONFIG_XXX"   "select module be compiled,define on config.mk,
	@echo "                   "CONFIG_MODULE = y
	@echo "                   "CONFIG_ENV      = "abc"
	@echo "    "SRCS-y"       "select file be compiled
	@echo "                   "SRCS-y += src/main.c src/foo.c
	@echo "                   "SRCS-\(CONFIG_MODULE\) += mod/module.c
# user define

rmdb:
	@-rm /etc/xx.db
sqlite3:
	sqlite3 /etc/xx.db


copy:
	cp $(OUTPUT_DIR)-$(ARCH)/$(OUTPUT_ELF) /mnt/nfs/$(OUTPUT_ELF)

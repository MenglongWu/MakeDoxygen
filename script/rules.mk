#################################################################
# load default project configure: script/project.mk
ifeq ("$(project)", "")
	ifeq (script/project.mk, $(wildcard script/project.mk))
		include script/project.mk
	endif
else
	include $(project)
endif




#################################################################
# select which file be complie,it edit in config_app_file.mk
# Import all files,it edit in config_xxx_file_list.mk
ifeq ("$(file_config)", "")
	ifeq (config.mk, $(wildcard config.mk))
		include config.mk
	endif
else
	include $(file_config)
endif

ifeq ("$(file_list)", "")
	ifeq (config_app_file_list.mk, $(wildcard config_app_file_list.mk))
		include config_app_file_list.mk
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

MAKE_DIR	+= include 




#################################################################
# macro NOWTIME "yyyy-mm-dd_HH:MM:SS"
BUILD_DATE="$(shell date "+%Y-%m-%d %H:%M:%S")"

#################################################################
# INCLUDE_DIR	- Where will be search *.h file
# LFLAGS		- Linking option
# LIB_DIR		- Where will be search *.so/*.a file
#-Wl,-rpath=./:./lib/

#when app.elf run will select *.so/a from $(PATH) -> ./ -> ./lib/
INCLUDE_DIR	+= 
LFLAGS		+= 
LIB_DIR 	+= 
CFLAGS      += -DBUILD_DATE=\"$(BUILD_DATE)\"  -DPRJ_VERSION=\"$(PRJ_VERSION)\" -DPRJ_NAME=\"$(PRJ_NAME)\"



ifeq ("$(OUTPUT_DIR)", "")
	OUTPUT_DIR=debug
endif

ifeq ("$(CROSS_COMPILE)", "")
else
endif


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
ifeq ("$(GCC_G++)","gcc")
	CC_FLAGS    = -std=gnu99
else
	CC_FLAGS    = 
endif
CS_FLAGS    = 


CC_FLAGS   += $(CFLAGS)
CS_FLAGS   += $(CFLAGS)

ifeq ("$(load_lds)","y") 
	load_lds = load_lds-y
else
	load_lds = load_lds-n
endif


all:$(load_lds)
	echo kkkkkkkk
configure: init_dir
	@mheader config.mk include/autoconfig.h $(PRJ_NAME)

#################################################################
# 
load_lds-n:$(OUTPUT_DIR) $(OBJS)
	@echo "    " create $(OUTPUT_DIR)/$(OUTPUT_ELF)
	@$(CC) -o $(OUTPUT_DIR)/$(OUTPUT_ELF) $(OBJS) $(LIB_DIR) $(LFLAGS)

	@echo "    " create $(OUTPUT_DIR)/$(OUTPUT_DIS)
	@$(OBJDUMP) -S $(OUTPUT_DIR)/$(OUTPUT_ELF) > $(OUTPUT_DIR)/$(OUTPUT_DIS)


load_lds-y:$(OUTPUT_DIR) $(OBJS)

	@echo "    " create $(OUTPUT_DIR)/$(OUTPUT_ELF)
	@$(LD) -Tboot.lds $(OBJS) -o $(OUTPUT_DIR)/$(OUTPUT_ELF) $(LFLAGS) $(LIB_DIR)  
	
	@echo "    " create $(OUTPUT_DIR)/$(OUTPUT_BIN)
	@$(OBJCOPY) -O binary -S $(OUTPUT_DIR)/$(OUTPUT_ELF) $(OUTPUT_DIR)/$(OUTPUT_BIN)


	@echo "    " create $(OUTPUT_DIR)/$(OUTPUT_DIS)
	@$(OBJDUMP) -S $(OUTPUT_DIR)/$(OUTPUT_ELF) > $(OUTPUT_DIR)/$(OUTPUT_DIS)
#################################################################
library:$(OBJS)
	$(CC) -shared -fPIC -o $(OUTPUT_DIR)/$(OUTPUT_SO) $(OBJS)

#################################################################
%.o:%.c
	@echo "    " compile $^
	@$(CC) -o $@ -c $^ $(CC_FLAGS) $(INCLUDE_DIR)
%.o:%.cpp
	@echo "    " compile $^
	@$(CC) -o $@ -c $^ $(CC_FLAGS) $(INCLUDE_DIR) 
%.o:%.S
	@echo "    " compile $^
	@$(CC) -o $@ -c $^ $(CS_FLAGS) $(INCLUDE_DIR)


# make directory
$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

init_dir:$(MAKE_DIR)

$(MAKE_DIR):
	mkdir $@ 


.PHONY: clean disclean
clean:
	@-rm $(OBJS)  \
		$(OUTPUT_DIR)/$(OUTPUT_DIS) \
		$(OUTPUT_DIR)/$(OUTPUT_ELF) \
		$(OUTPUT_DIR)/$(OUTPUT_BIN) \
		$(OUTPUT_DIR)/$(OUTPUT_SO) \
		$(OUTPUT_DIR)/$(OUTPUT_A)
	@-rm -f core

run:
	./$(OUTPUT_DIR)/$(OUTPUT_ELF)

gdb:
	gdb ./$(OUTPUT_DIR)/$(OUTPUT_ELF)
gdb-core:
	gdb ./$(OUTPUT_DIR)/$(OUTPUT_ELF) core


print_env:
	@echo PRJ_VERSION = $(PRJ_VERSION)
	@echo PRJ_NAME = $(PRJ_NAME)

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
	@echo INCLUDE_DIR "  " = $(INCLUDE_DIR)
	@echo LFLAGS "  " = $(LFLAGS)
	@echo LIB_DIR "  " = $(LIB_DIR)
	@echo CFLAGS "  " = $(CFLAGS)

	@echo SRCS-y = $(SRCS-y)
# user define


rmoutput:$(OUTPUT_DIR)
	@-rm -rf $(OUTPUT_DIR)

rmdb:
	@-rm /etc/xx.db
sqlite3:
	sqlite3 /etc/xx.db


copy:
	cp ./$(OUTPUT_DIR)/$(OUTPUT_ELF) /mnt/nfs/OUTPUT_ELF

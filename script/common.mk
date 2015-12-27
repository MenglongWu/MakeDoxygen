#################################################################
# config your default value
# ARCH=xxxx

SUPPOR_ARCH = x86 arm920t armv7 i586
# ifneq ($(ARCH) , $(filter $(SUPPOR_ARCH), $(ARCH)) )
# # $(warning  "file_list undefinessssssssd")
# 	$(error  file_list undefinessssssssd)
# endif


ifeq ("$(ARCH)", "")
	ARCH=x86
endif

ifeq ("$(ARCH)", "arm920t")
	CROSS_COMPILE	=/opt/EmbedSky/crosstools_3.4.5_softfloat/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-
endif

ifeq ("$(ARCH)", "armv7")
	CROSS_COMPILE	=/opt/iTop-4412/4.3.2/bin/arm-linux-
endif

ifeq ("$(ARCH)", "i586")
	CROSS_COMPILE	=i586-mingw32msvc-
endif
# todo More


#################################################################
# INCLUDE_DIR	- Where will be search *.h file
# LFLAGS		- Linking option
# LIB_DIR		- Where will be search *.so/*.a file
#-Wl,-rpath=./:./lib/

#when app.elf run will select *.so/a from $(PATH) -> ./ -> ./lib/
INCLUDE_DIR = -I./ -I./include
LFLAGS	    =
LIB_DIR     = 
CFLAGS      = 
CS_FLAGS    = 

ifeq ("$(ARCH)", "x86")
	INCLUDE_DIR	+= 
	LFLAGS		+= -Wl,-rpath=./:lib-x86/
	LIB_DIR 	+= -L/usr/local/install/lib
	CFLAGS		+= -DTARGET_X86
endif

ifeq ("$(ARCH)", "armv7")
	INCLUDE_DIR	+= -I/usr/4412/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-armv7/
	LIB_DIR 	+= -L/usr/4412/install/lib
	CFLAGS		+= -DTARGET_ARMV7
endif


ifeq ("$(ARCH)", "arm920t")
	INCLUDE_DIR	+= -I/usr/arm920t/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-arm920t/
	LIB_DIR 	+= -L/usr/arm920t/install/lib
	CFLAGS		+= -DTARGET_ARM920T
endif


ifeq ("$(ARCH)", "i586")
	INCLUDE_DIR	+= -I/usr/win32/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-win32/
	LIB_DIR 	+= -L/usr/win32/install/lib
	CFLAGS		+= -DTARGET_WIN32
endif
#################################################################


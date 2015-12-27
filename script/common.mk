#################################################################
# config your default value
# ARCH=xxxx

# ARCH=x
SUPPORT_TARGET=x86 arm920t armv7 win32
ifeq ("$(ARCH)", "")
	ARCH=x86
endif

ifeq ("$(ARCH)", "arm920t")
	CROSS_COMPILE	=/opt/EmbedSky/crosstools_3.4.5_softfloat/gcc-3.4.5-glibc-2.3.6/arm-linux/bin/arm-linux-
endif

ifeq ("$(ARCH)", "armv7")
	CROSS_COMPILE	=/opt/iTop-4412/4.3.2/bin/arm-linux-
endif

ifeq ("$(ARCH)", "win32")
	CROSS_COMPILE	=i586-mingw32msvc-
endif
# todo More
# ifeq ("$(ARCH)", "your_target")
# 	CROSS_COMPILE	= your crosstools directory
# endif



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
	LIB_DIR 	+= -L/usr/local/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_X86
endif

ifeq ("$(ARCH)", "armv7")
	INCLUDE_DIR	+= -I/usr/4412/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-armv7/
	LIB_DIR 	+= -L/usr/4412/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_ARMV7
endif


ifeq ("$(ARCH)", "arm920t")
	INCLUDE_DIR	+= -I/usr/arm920t/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-arm920t/
	LIB_DIR 	+= -L/usr/arm920t/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_ARM920T
endif


ifeq ("$(ARCH)", "win32")
	INCLUDE_DIR	+= -I/usr/win32/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/win32/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_WIN32
endif

# todo More
#ifeq ("$(ARCH)", "your_target")
#	INCLUDE_DIR	+= -I/usr/your_target/install/include
#	LFLAGS		+= -Wl,-rpath=./:./lib-$(ARCH)/
#	LIB_DIR 	+= -L/usr/your_target/install/lib -L./lib-$(ARCH)
#	CFLAGS		+= -DTARGET_your_target
endif
# endif
#################################################################


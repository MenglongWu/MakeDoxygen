#################################################################
# config your default value

PRJ_VERSION    = "1"
PRJ_PATCHLEVEL = "0"
PRJ_SUBLEVEL   = "0"


SUPPORT_TARGET=x86 arm920t armv7 win32  arm926

COPY_DIR=./
# COPY_DIR=/nfs
# COPY_DIR=/tftp

# ARCH=xxxx
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
ifeq ("$(ARCH)", "arm926")
	CROSS_COMPILE	=/opt/EasyArm/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-linux-
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
	LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/local/install/lib -L./lib-$(ARCH)
	CFLAGS		+=
endif

ifeq ("$(ARCH)", "armv7")
	INCLUDE_DIR	+= -I/usr/4412/install/include
	LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/4412/install/lib -L./lib-$(ARCH)
	CFLAGS		+=
endif


ifeq ("$(ARCH)", "arm920t")
	INCLUDE_DIR	+= -I/usr/arm920t/install/include
	LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/arm920t/install/lib -L./lib-$(ARCH)
	CFLAGS		+=
endif


ifeq ("$(ARCH)", "win32")
	INCLUDE_DIR	+= -I/usr/win32/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/win32/install/lib -L./lib-$(ARCH)
	CFLAGS		+=
endif
 

ifeq ("$(ARCH)", "arm926")
	INCLUDE_DIR	+= -I/usr/arm926/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-$(ARCH)/
	LIB_DIR 	+= -L/usr/arm926/install/lib -L./lib-$(ARCH)
	CFLAGS		+=
endif
# todo More
#ifeq ("$(ARCH)", "your_target")
#	INCLUDE_DIR	+= -I/usr/your_target/install/include
#	LFLAGS		+= -Wl,-rpath=./:./lib-$(ARCH)/
#	LIB_DIR 	+= -L/usr/your_target/install/lib -L./lib-$(ARCH)
#	CFLAGS		+=
# endif
#################################################################


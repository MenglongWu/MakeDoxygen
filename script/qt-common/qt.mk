# only a Qt example 
#

# 'GCHS_INCLUDE_DIR' is different to 'INCLUDE_DIR', 'GCHS_INCLUDE_DIR' only for
# precompile
#
GCHS_INCLUDE_DIR	+= -I./ -I./src \
		-I/opt/EasyArm/qt/include \
		-I/opt/EasyArm/qt/include/Qt \
		-I/opt/EasyArm/qt/include/QtGui \
		-I/opt/EasyArm/qt/include/QtCore
LFLAGS		+= -lQtGui -lQtCore -lQtNetwork  -lpng -lz
LIB_DIR += -L/opt/EasyArm/qt/lib \
	   -L/work/EasyArm/rootfs/rootfs/usr/lib
CFLAGS  +=



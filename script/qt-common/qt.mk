# only a Qt example 
#

# 'GCHS_INCLUDE_DIR' is different to 'INCLUDE_DIR', 'GCHS_INCLUDE_DIR' only for
# precompile
#

QT_INCLUDE=/opt/EasyArm/qt/include
QT_LIB=/opt/EasyArm/qt/lib 
GCHS_INCLUDE_DIR += \
		-I$(QT_INCLUDE) \
		-I$(QT_INCLUDE)/Qt \
		-I$(QT_INCLUDE)/QtGui \
		-I$(QT_INCLUDE)/QtCore
LFLAGS		+= -lQtGui -lQtCore -lQtNetwork  -lz
LIB_DIR += -L$(QT_LIB)
	   # -L/work/EasyArm/rootfs/rootfs/usr/lib
CFLAGS  +=



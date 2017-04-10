
SRCS-y += src/qt-moc.cpp
SRCS-y += src/dlg-net.cpp



GCHS-y += src/qt.hpp.gch  

MOCS-y = src/dlg-net.moc.cpp

SRCS-y += $(MOCS-y)

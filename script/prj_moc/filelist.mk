
SRCS-y += src/qt/qt-moc.cpp
SRCS-y += src/qt/dlg-net.cpp



GCHS-y += src/qt/qt.hpp.gch  

MOCS-y = src/qt/dlg-net.moc.cpp

SRCS-y += $(MOCS-y)

# # 最小系统代码
SRCS-y += src/qt-moc.cpp
SRCS-y += src/dlg-net.cpp



# PRE = src/qt.hpp
GCHS-y += src/qt.hpp.gch  

# MOCS-y = src/dlgmy.moc.cpp
MOCS-y = src/dlg-net.moc.cpp

SRCS-y += $(MOCS-y)

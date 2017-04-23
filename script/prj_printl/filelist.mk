# # 最小系统代码

GCHS_INCLUDE_DIR=-I./include

SRCS-y += src/printl/t-printl.c
SRCS-y += src/printl/dev1.c
SRCS-y += src/printl/dev2.c
# SRCS-y += src/printl_common.c

GCHS-y+=include/printl.h.gch
GCHS-y+=src/printl/dev1-private.h.gch
GCHS-y+=src/printl/dev2-private.h.gch

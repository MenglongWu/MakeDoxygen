#################################################################
# list all souce file while be compiled
# file select or not please edit script/config.mk
SRCS-y	+= 	src/la/la_part1.c

SRCS-$(CONFIG_USE_LA_PART2) += src/la/la_part2.c
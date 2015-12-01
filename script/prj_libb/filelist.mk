#################################################################
# list all souce file while be compiled
# file select or not please edit script/config.mk
SRCS-y	+= 	src/lb/lb_part1.c

SRCS-$(CONFIG_USE_LB_PART2) += src/lb/lb_part2.c

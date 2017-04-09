#################################################################
# you can edit it for all target
# create all project target with sequence
PRJS-y:= pi1 pi2 pi3
PRJS-$(CONFIG_QT) += pi4 pi5 pi6  


# pi1 -> default.elf 
#	depends 
#		libla.so liblb.so
# pi2 -> libla.so
# pi3 -> libla.so
pi1:pi2 pi3

pi5:pi6

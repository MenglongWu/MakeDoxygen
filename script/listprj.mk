#################################################################
# rule
# path must be a directory, exist path/project.mk,path/filelist.mk
#
# pixxx=script/default
# pixxx_arg=[all,mlib,elf...] one of us, [all, mlib,elf...] is top path Makefile operation
	pi1=script/default
		pi1_arg=elf

	pi2=script/prj_liba
		pi2_arg=mlib

	pi3=script/prj_libb
		pi3_arg=mlib
	pi4=script/prj_qt
		pi4_arg=elf
	pi5=script/prj_cpp_c
		pi5_arg=elf
	pi6=script/prj_moc
		pi6_arg=elf
	pi7=script/prj_printl
		pi7_arg=elf




# default project item
export DP=pi7
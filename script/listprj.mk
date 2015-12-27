#################################################################
# rule
# path must be a directory, exist path/project.mk,path/filelist.mk
#
# pixxx=script/default
# pixxx_arg=[all,mlib,elf...] one of us, [all, mlib,elf...] is top path Makefile operation
	pi1=script/default
		pi1_arg=bin

	pi2=script/prj_liba
		pi2_arg=mlib

	pi3=script/prj_libb
		pi3_arg=mlib

# default project item
export DP=pi1

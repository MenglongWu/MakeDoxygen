	pi1=script/default
		pi1_arg=all

	pi2=script/prj_liba
		pi2_arg=mlib

	pi3=script/prj_libb
		pi3_arg=mlib

DP=pi1
ARG=$($(DP)_arg)
file_prj  =$($(DP))/project.mk
file_list =$($(DP))/filelist.mk
#################################################################
# you can edit it for all target
# create all project target with sequence

.PHONY:allp
allp:
	$(MAKE) DP=pi2
	$(MAKE) DP=pi3
	$(MAKE) DP=pi1

# clean all project output
.PHONY:allclean
allclean:
	$(MAKE) DP=pi2 clean
	$(MAKE) DP=pi3 clean
	$(MAKE) DP=pi1 clean
# remote all output file and empty directory which create by Makefile
.PHONY:alldisclean
alldisclean:
	$(MAKE) DP=pi2 disclean
	$(MAKE) DP=pi3 disclean
	$(MAKE) DP=pi1 disclean
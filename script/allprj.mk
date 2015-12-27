#################################################################
# you can edit it for all target
# create all project target with sequence

.PHONY:allp
allp:
	$(MAKE) DP=pi2 --no-print-directory
	$(MAKE) DP=pi3 --no-print-directory
	$(MAKE) DP=pi1 --no-print-directory

# clean all project output
.PHONY:allclean
allclean:
	$(MAKE) DP=pi2 clean --no-print-directory
	$(MAKE) DP=pi3 clean --no-print-directory
	$(MAKE) DP=pi1 clean --no-print-directory

# remote all output file and empty directory which create by Makefile
.PHONY:alldisclean
alldisclean:
	$(MAKE) DP=pi2 disclean --no-print-directory
	$(MAKE) DP=pi3 disclean --no-print-directory
	$(MAKE) DP=pi1 disclean --no-print-directory
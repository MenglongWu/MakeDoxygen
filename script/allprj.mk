#################################################################

# create all project target with sequence
allp:
	$(MAKE) DP=pi2
	$(MAKE) DP=pi3
	$(MAKE) DP=pi1

# clean all project output
allclean:
	make DP=pi2 clean
	make DP=pi3 clean
	make DP=pi1 clean
#!/bin/sh

# call by Makefile
# .sha1 file create depend on .git directory 
# .git/HEAD and git/refs/<branch>

# if your environment is that
# ---------------------------------------
# ~ $ cat .git/HEAD 
# ref: refs/heads/develop

# in Makefile

#              |<--- this sha1dep.sh return --->|
# sha1_dep =   .git/HEAD .git/refs/heads/develop
# .sha1:$(sha1_dep)
# 		TODO ...
# ---------------------------------------



if [ -f ".git/HEAD" ]
then
	head=$(cat .git/HEAD  |  awk '{print $2}')
	echo .git/HEAD
	echo .git/${head}
fi
echo ""


#!/bin/sh

# call by Makefile
# get Git SHA1 node ID save in .sha1 file



if [ -f ".git/HEAD" ]
then
	head=$(cat .git/HEAD  |  awk '{print $2}')
	sha1=$(cat .git/${head})
	echo ${sha1}
fi
echo ""


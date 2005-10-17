#!/bin/sh
# This little script just does all the commands needed to make and install libease
make clean
make uninstall
# Compile the file itself
make
# Check the file was compiled correctly
if [ -e "libease.so.0.0.1" ]
then
	make install
	make test
else
	echo "I am sorry to say that the program didnt compile for some reason"
	echo "Please report this to stroppytux@gmail.com with any additional"
	echo "information."
fi
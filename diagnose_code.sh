#!/bin/zsh

# Please change these paths to suit your environment configurations (where the tools were installed)
GCC_PATH=/usr/local/bin/gcc-13
FLAWFINDER_PATH=/usr/local/bin/flawfinder
CPPCHECK_PATH=./cppcheckpremium/cppcheck
if [[ -n $1 ]]
then
	COLLECTED_CODE=$1/*
else
	COLLECTED_CODE=./*
fi

for file in $COLLECTED_CODE ; do
	if [ "${file: -2}" == ".c" ] ; then
		$GCC_PATH -o ${file//.c/.o} $file # compile the code
		$GCC_PATH -fanalyzer $file 1> ${file//.c/.gcc.txt} 2> ${file//.c/.gcc.txt} & # analyze by GCC
		$FLAWFINDER_PATH $file 1> ${file//.c/.flawfinder.txt} 2> ${file//.c/.flawfinder.txt} & # analyze by Flawfinder
		$CPPCHECK_PATH --premium=bughunting $file 1> ${file//.c/.cppcheck.txt} 2> ${file//.c/.cppcheck.txt} & # analyze by cppcheck
	fi
done

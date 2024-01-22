#!/bin/bash

# Please change these paths to suit your environment configurations (where the tools were installed)
GCC_PATH=/usr/local/bin/gcc-13
FLAWFINDER_PATH=/usr/local/bin/flawfinder
CPPCHECK_PATH=./cppcheckpremium/cppcheck

COLLECTED_CODE=collected_code/heal_round_$1/healed/*

for file in $COLLECTED_CODE ; do
	if [ "${file: -2}" == ".c" ] ; then
		$GCC_PATH -o ${file//.c/.o} $file
		$GCC_PATH -fanalyzer $file 1> ${file//.c/.gcc.txt} 2> ${file//.c/.gcc.txt} &
		$FLAWFINDER_PATH $file 1> ${file//.c/.flawfinder.txt} 2> ${file//.c/.flawfinder.txt} &
		$CPPCHECK_PATH --premium=bughunting $file 1> ${file//.c/.cppcheck.txt} 2> ${file//.c/.cppcheck.txt} &
	fi
done

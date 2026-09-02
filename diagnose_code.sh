#!/bin/zsh

# Please change these paths to suit your environment configurations (where the tools were installed)
#GCC_PATH=/usr/local/bin/gcc-13
#CLANG_PATH=/usr/bin/clang
CLANG_PATH=/usr/local/opt/llvm/bin/clang
#Z3_PATH=/usr/local/bin/z3
file=$1
# $GCC_PATH -fanalyzer $file 1> ${file//.c/.gcc.txt} 2> ${file//.c/.gcc.txt}
$CLANG_PATH --analyze -Xclang -analyzer-config -Xclang crosscheck-with-z3=true $file 1> ${file//.c/.clang.txt} 2> ${file//.c/.clang.txt}
#$Z3_PATH $file 1> ${file//.c/.z3.txt} 2> ${file//.c/.z3.txt}
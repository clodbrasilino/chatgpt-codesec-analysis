#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int **generate_magic_square(int n)
{
    int **square;
    int row;
    int col;
    int num;
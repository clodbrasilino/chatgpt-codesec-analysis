#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_int(int *val) {
    int c;
    int sign = 1;
    while ((c = getchar()) != EOF && !isdigit(c) && c != '-');
    if (c == EOF) return 0;
    if (c == '-') {
        sign = -1;
        c = getchar();
        if (c == EOF || !isdigit(c)) return 0;
    }
    long long temp = c - '0';
    while ((c = getchar()) != EOF && isdigit(c)) {
        temp = temp * 10 + (c
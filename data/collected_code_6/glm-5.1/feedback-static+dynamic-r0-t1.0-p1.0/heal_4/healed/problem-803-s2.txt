#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)round(sqrt((double)num));
    if (root * root == num) {
        return 1;
    }
    root++;
    if (root * root == num) {
        return 1;
    }
    root -= 2;
    if (root * root == num) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }
    if (argv[1][0] == '\0') {
        return 1;
    }
    char *endptr;
    errno = 0;
    long long val = strtoll(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return 1;
    }
    int result = is_perfect_square(val);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}
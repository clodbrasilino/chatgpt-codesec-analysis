#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
}

int main(int argc, char * const * argv) {
    long long num;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    num = strtoll(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || num < INT_MIN || num > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int pos = get_rightmost_set_bit((int)num);
    if (pos == -1) {
        printf("0\n");
    } else {
        printf("%d\n", pos);
    }
    return EXIT_SUCCESS;
}
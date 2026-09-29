#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    int n = (int)val;
    int pos = get_rightmost_set_bit(n);

    printf("%d\n", pos);

    return EXIT_SUCCESS;
}
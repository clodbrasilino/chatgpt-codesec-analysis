#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return 0;
    }
    return n & (-n);
}

int main(int argc, char * const argv[static const 2]) {
    long val;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int pos = get_rightmost_set_bit(n);
    printf("%d\n", pos);
    return EXIT_SUCCESS;
}
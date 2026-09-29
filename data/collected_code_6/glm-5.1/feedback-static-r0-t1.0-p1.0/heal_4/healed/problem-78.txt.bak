#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_odd_set_bits(int n) {
    if (n < 0) {
        return -1;
    }
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (__builtin_parity(i) != 0) {
            count++;
        }
    }
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = count_odd_set_bits(n);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
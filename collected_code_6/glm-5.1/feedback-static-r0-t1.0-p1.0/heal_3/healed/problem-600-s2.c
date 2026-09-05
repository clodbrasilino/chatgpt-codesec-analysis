#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_even(int num) {
    return (num & 1) == 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return 1;
    }

    int num = (int)val;
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}
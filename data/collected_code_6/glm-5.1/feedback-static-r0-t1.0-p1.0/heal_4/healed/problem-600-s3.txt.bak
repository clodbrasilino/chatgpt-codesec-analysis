#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_even(int num) {
    return (num & 1) == 0;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return EXIT_SUCCESS;
}
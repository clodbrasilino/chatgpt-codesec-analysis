#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_odd(int num) {
    return num & 1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    if (is_odd(num)) {
        printf("Odd\n");
    } else {
        printf("Even\n");
    }

    return EXIT_SUCCESS;
}
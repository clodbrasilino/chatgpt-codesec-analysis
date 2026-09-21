#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_scalene(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a != b && b != c && a != c) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val;
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int a = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || endptr == argv[2] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int b = (int)val;

    errno = 0;
    val = strtol(argv[3], &endptr, 10);
    if (errno != 0 || endptr == argv[3] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int c = (int)val;

    if (is_scalene(a, b, c)) {
        printf("Scalene\n");
    } else {
        printf("Not Scalene\n");
    }
    return EXIT_SUCCESS;
}
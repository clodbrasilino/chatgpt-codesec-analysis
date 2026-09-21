#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(int number) {
    if (number == 0) {
        return 1;
    }
    int count = 0;
    unsigned int n;
    if (number == INT_MIN) {
        n = (unsigned int)number;
    } else if (number < 0) {
        n = (unsigned int)(-number);
    } else {
        n = (unsigned int)number;
    }
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int main(int argc, char const * const argv[]) {
    int number;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    number = (int)val;
    printf("%d\n", count_digits(number));
    return EXIT_SUCCESS;
}
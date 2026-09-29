#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_in_sequence(int num) {
    if (num <= 0) {
        return 0;
    }
    while (num % 3 == 0) {
        num /= 3;
    }
    return num == 1;
}

int main(int argc, char * const argv[]) {
    int number;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a valid integer between 0 and %d\n", INT_MAX);
        return EXIT_FAILURE;
    }
    number = (int)val;
    if (is_in_sequence(number)) {
        printf("%d is in the sequence\n", number);
    } else {
        printf("%d is not in the sequence\n", number);
    }
    return EXIT_SUCCESS;
}
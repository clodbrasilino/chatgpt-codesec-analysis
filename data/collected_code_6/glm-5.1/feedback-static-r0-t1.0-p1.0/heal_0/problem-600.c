#include <stdio.h>
#include <stdlib.h>

int is_even(int num) {
    return (num & 1) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer format.\n");
        return EXIT_FAILURE;
    }

    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Error: Integer out of range.\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }

    return EXIT_SUCCESS;
}
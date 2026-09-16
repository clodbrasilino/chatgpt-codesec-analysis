#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long value = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || value < 0) {
        fprintf(stderr, "Error: Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", sum_of_digits((int)value));
    return EXIT_SUCCESS;
}
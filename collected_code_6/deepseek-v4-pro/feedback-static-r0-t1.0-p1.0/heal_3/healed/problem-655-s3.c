#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

unsigned long long sum_fifth_power(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i * i * i;
        sum += term;
    }
    return sum;
}

int main(void) {
    char input[128];
    char *endptr;

    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    endptr = input;
    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr == '\0') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long val = strtol(endptr, &endptr, 10);

    if (endptr == input || (*endptr != '\0' && !isspace((unsigned char)*endptr))) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Number out of range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;

    if (n <= 0) {
        fprintf(stderr, "Number must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers: %llu\n", sum_fifth_power(n));
    return EXIT_SUCCESS;
}
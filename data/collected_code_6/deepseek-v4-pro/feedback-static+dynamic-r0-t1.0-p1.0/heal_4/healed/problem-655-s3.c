#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 64

unsigned long long sum_fifth_power(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i * i * i;
        if (sum > ULLONG_MAX - term) {
            return ULLONG_MAX;
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    long val;
    size_t len;
    size_t i;

    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }
    if (len == sizeof(input)) {
        input[sizeof(input) - 1] = '\0';
        len = sizeof(input) - 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == '\0') {
            break;
        }
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Number out of range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;

    if (n <= 0) {
        fprintf(stderr, "Number must be positive.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_fifth_power(n);
    if (result == ULLONG_MAX) {
        fprintf(stderr, "Result overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers: %llu\n", result);
    return EXIT_SUCCESS;
}
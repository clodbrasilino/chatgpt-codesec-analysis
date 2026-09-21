#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define INPUT_SIZE 64

long long rectangular_number(int n) {
    if (n < 1) {
        return -1;
    }
    if ((long long)n > LLONG_MAX / ((long long)n + 1)) {
        return -1;
    }
    return (long long)n * ((long long)n + 1);
}

int main(void) {
    char input[INPUT_SIZE];
    char *endptr;
    long val;
    long long result;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len == 0 || len == sizeof(input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (val < 1 || val > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    result = rectangular_number((int)val);

    if (result == -1) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
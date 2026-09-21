#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;
    char *endptr;
    long val;
    long long result;

    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (val < 1 || val > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        free(input);
        return EXIT_FAILURE;
    }

    result = rectangular_number((int)val);

    free(input);

    if (result == -1) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
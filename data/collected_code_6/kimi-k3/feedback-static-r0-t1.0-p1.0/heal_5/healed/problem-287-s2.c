#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

unsigned long long sum_of_squares_even(int n) {
    unsigned long long sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * (unsigned int)i;
        sum += even_num * even_num;
    }
    return sum;
}

int main(void) {
    char buffer[4096];
    char *endptr;
    long val;
    int n;
    unsigned long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = sum_of_squares_even(n);
    
    if (printf("%llu\n", result) < 0) {
        fprintf(stderr, "Error writing output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
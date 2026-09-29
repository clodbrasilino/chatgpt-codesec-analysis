#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

double geometric_sum(int n) {
    double result = 0.0;
    double term = 1.0;
    int i;

    if (n < 1) {
        return 0.0;
    }

    for (i = 0; i < n; i++) {
        result += term;
        term /= 2.0;
    }

    printf("%.10f\n", result);
    fflush(stdout);
    return result;
}

int main(void) {
    char buffer[256] = {0};
    long input_val;
    int n;
    size_t len;

    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len >= sizeof(buffer) - 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0 || buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    {
        char *endptr;
        errno = 0;
        input_val = strtol(buffer, &endptr, 10);

        if (errno == ERANGE || input_val > INT_MAX || input_val < INT_MIN) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        if (endptr == buffer || *endptr != '\0') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    n = (int)input_val;

    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }

    geometric_sum(n);
    return EXIT_SUCCESS;
}
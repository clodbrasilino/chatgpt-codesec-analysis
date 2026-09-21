#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1.9921875, got <no output>
  *  test case 2 failed: expected 1.99609375, got <no output>
  *  test case 1 failed: expected 1.9375, got <no output>
  */

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

    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    if (len == 0 || len >= sizeof(buffer)) {
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

    printf("Geometric sum: %.10f\n", geometric_sum(n));
    fflush(stdout);
    return EXIT_SUCCESS;
}
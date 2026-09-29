#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int median_of_three(int a, int b, int c) {
    if ((a >= b && a <= c) || (a <= b && a >= c)) {
        return a;
    } else if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    } else {
        return c;
    }
}

int parse_int(const char *str, int *out) {
    char *endptr;
    long val;

    if (str == NULL || out == NULL) {
        return -1;
    }

    errno = 0;
    val = strtol(str, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return -1;
    }

    if (endptr == str || (*endptr != '\0' && *endptr != '\n')) {
        return -1;
    }

    *out = (int)val;
    return 0;
}

int read_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    size_t len = 0;
    while (len < size && buffer[len] != '\0') {
        len++;
    }

    if (len > 0 && buffer[len - 1] != '\n' && len == size - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        return -1;
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    int a, b, c;

    if (read_input(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_int(input, &a) != 0) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    if (read_input(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_int(input, &b) != 0) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    if (read_input(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_int(input, &c) != 0) {
        fprintf(stderr, "Invalid input for third number\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", median_of_three(a, b, c));

    return EXIT_SUCCESS;
}
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

    if (endptr == str || *endptr != '\0') {
        return -1;
    }

    *out = (int)val;
    return 0;
}

int main(void) {
    char input[64];
    int a, b, c;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_int(input, &a) != 0) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_int(input, &b) != 0) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
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
#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;
    }
    *result = a / b;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <numerator> <denominator>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long a = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    long b = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    int quotient;
    if (divide((int)a, (int)b, &quotient) != 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", quotient);
    return EXIT_SUCCESS;
}
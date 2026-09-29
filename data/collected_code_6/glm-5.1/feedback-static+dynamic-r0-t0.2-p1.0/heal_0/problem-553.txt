#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int tuple_to_float(const Tuple *t, float *result) {
    if (t == NULL || result == NULL) {
        return -1;
    }

    if (t->denominator == 0) {
        return -2;
    }

    *result = (float)t->numerator / (float)t->denominator;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <numerator> <denominator>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long num = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    long den = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    Tuple t;
    t.numerator = (int)num;
    t.denominator = (int)den;

    float result;
    int ret = tuple_to_float(&t, &result);

    if (ret == 0) {
        printf("%f\n", result);
        return EXIT_SUCCESS;
    } else if (ret == -2) {
        fprintf(stderr, "Division by zero\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
}
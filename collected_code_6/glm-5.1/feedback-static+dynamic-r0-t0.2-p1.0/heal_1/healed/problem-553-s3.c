#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int tuple_to_float(const Tuple *t, float *out) {
    if (t == NULL || out == NULL) {
        return -1;
    }
    if (t->denominator == 0) {
        return -1;
    }
    *out = (float)t->numerator / (float)t->denominator;
    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <numerator> <denominator>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long num = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno != 0 || num < INT_MIN || num > INT_MAX) {
        return EXIT_FAILURE;
    }
    errno = 0;
    long den = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || errno != 0 || den < INT_MIN || den > INT_MAX) {
        return EXIT_FAILURE;
    }
    Tuple t;
    t.numerator = (int)num;
    t.denominator = (int)den;
    float result;
    if (tuple_to_float(&t, &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    printf("%f\n", result);
    return EXIT_SUCCESS;
}
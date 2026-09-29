#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int tuple_to_float(const Tuple *t, double *result) {
    if (t == NULL || result == NULL) {
        errno = EINVAL;
        return 0;
    }
    if (t->denominator == 0) {
        errno = EDOM;
        return 0;
    }
    *result = (double)t->numerator / (double)t->denominator;
    return 1;
}

int main(void) {
    Tuple input = {1, 2};
    double output;

    if (!tuple_to_float(&input, &output)) {
        perror("tuple_to_float");
        return EXIT_FAILURE;
    }

    printf("%f\n", output);
    return EXIT_SUCCESS;
}
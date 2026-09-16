#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stddef.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got nan
  *  test case 0 failed: expected 4.56, got nan
  *  test case 2 failed: expected 8.123, got nan
  */

float tuple_to_float(const Tuple *t) {
    if (t == NULL) {
        errno = EINVAL;
        return NAN;
    }

    if (t->denominator == 0) {
        errno = EDOM;
        return NAN;
    }

    return (float)t->numerator / (float)t->denominator;
}

int main(void) {
    Tuple t = {1, 2};
    float result;

    errno = 0;
    result = tuple_to_float(&t);

    if (errno != 0) {
        fprintf(stderr, "Error converting tuple\n");
        return 1;
    }

    printf("%.6f\n", result);
    return 0;
}
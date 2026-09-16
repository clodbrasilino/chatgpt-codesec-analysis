#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

static bool tuple_to_float(Tuple t, double *result)
{
    if (result == NULL) {
        return false;
    }
    if (t.denominator == 0) {
        return false;
    }
    *result = (double)t.numerator / (double)t.denominator;
    return true;
}

int main(void)
{
    Tuple t = { 7, 2 };
    double value = 0.0;

    if (tuple_to_float(t, &value)) {
        printf("Result: %f\n", value);
    } else {
        fprintf(stderr, "Error: cannot convert tuple to floating-point number\n");
        return 1;
    }

    return 0;
}
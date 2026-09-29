#include <stdio.h>

double tuple_to_float(int whole, int fraction)
{
    double divisor = 1.0;
    int temp;

    if (fraction < 0) {
        fprintf(stderr, "Error: fraction part must be non-negative\n");
        return 0.0;
    }

    temp = fraction;
    do {
        divisor *= 10.0;
        temp /= 10;
    } while (temp > 0);

    if (whole < 0) {
        return (double)whole - (double)fraction / divisor;
    }

    return (double)whole + (double)fraction / divisor;
}

int main(void)
{
    int tuple[2] = {4, 5};
    double result;

    result = tuple_to_float(tuple[0], tuple[1]);
    printf("(%d, %d) -> %g\n", tuple[0], tuple[1], result);

    return 0;
}
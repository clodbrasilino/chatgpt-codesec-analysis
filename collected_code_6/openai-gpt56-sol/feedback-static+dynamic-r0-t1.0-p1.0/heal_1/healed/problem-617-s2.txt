#include <stdio.h>
#include <limits.h>
#include <math.h>

static int minimum_jumps(double jump_length, double distance,
                         long long *result)
{
    if (result == NULL ||
        !isfinite(jump_length) ||
        !isfinite(distance) ||
        jump_length <= 0.0 ||
        distance < 0.0) {
        return 0;
    }

    if (distance == 0.0) {
        *result = 0;
        return 1;
    }

    if (distance == jump_length) {
        *result = 1;
        return 1;
    }

    if (distance < jump_length) {
        *result = 2;
        return 1;
    }

    double quotient = distance / jump_length;

    if (!isfinite(quotient) || quotient > (double)LLONG_MAX) {
        return 0;
    }

    double rounded = ceil(quotient);

    if (!isfinite(rounded) || rounded > (double)LLONG_MAX) {
        return 0;
    }

    *result = (long long)rounded;
    return 1;
}

int main(void)
{
    double jump_length;
    double distance;
    long long result;

    if (scanf("%lf %lf", &jump_length, &distance) != 2) {
        return 1;
    }

    if (!minimum_jumps(jump_length, distance, &result)) {
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}
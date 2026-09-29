#include <stdio.h>

static long long minimum_jumps(double jump_length, double distance)
{
    if (jump_length <= 0.0 || distance < 0.0) {
        return -1;
    }

    if (distance == 0.0) {
        return 0;
    }

    if (distance == jump_length) {
        return 1;
    }

    if (distance < jump_length) {
        return 2;
    }

    long long jumps = (long long)(distance / jump_length);

    if ((double)jumps * jump_length < distance) {
        ++jumps;
    }

    return jumps;
}

int main(void)
{
    double jump_length;
    double distance;

    if (scanf("%lf %lf", &jump_length, &distance) != 2) {
        return 1;
    }

    long long result = minimum_jumps(jump_length, distance);

    if (result < 0) {
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}
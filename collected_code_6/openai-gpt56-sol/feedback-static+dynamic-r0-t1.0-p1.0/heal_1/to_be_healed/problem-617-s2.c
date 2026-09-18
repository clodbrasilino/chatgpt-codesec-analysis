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

    /* Possible weaknesses found:
     * UBSan: 1.48148e+25 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:5775,execs:3038,op:havoc,rep:1)
     */
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
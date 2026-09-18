#include <stdio.h>
#include <stdlib.h>

static long minJumps(long jumpLength, long d)
{
    if (jumpLength <= 0 || d < 0)
    {
        return -1;
    }
    if (d == 0)
    {
        return 0;
    }
    if (d < jumpLength)
    {
        return 2;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 444444414 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000005,time:8460,execs:5365,op:havoc,rep:3)
     */
    return (d + jumpLength - 1) / jumpLength;
}

int main(void)
{
    long jumpLength = 0;
    long d = 0;
    long result = 0;

    printf("Enter jump length: ");
    if (scanf("%ld", &jumpLength) != 1)
    {
        fprintf(stderr, "Invalid input for jump length\n");
        return EXIT_FAILURE;
    }

    printf("Enter target distance d: ");
    if (scanf("%ld", &d) != 1)
    {
        fprintf(stderr, "Invalid input for distance\n");
        return EXIT_FAILURE;
    }

    result = minJumps(jumpLength, d);
    if (result < 0)
    {
        fprintf(stderr, "Invalid values: jump length must be positive and distance non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of jumps required: %ld\n", result);
    return EXIT_SUCCESS;
}
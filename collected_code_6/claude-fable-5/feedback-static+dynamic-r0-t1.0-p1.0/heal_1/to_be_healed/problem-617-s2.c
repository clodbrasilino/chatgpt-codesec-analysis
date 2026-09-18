#include <stdio.h>
#include <stdlib.h>

static long min_jumps(long step_length, long distance)
{
    if (step_length <= 0 || distance < 0) {
        return -1;
    }
    if (distance == 0) {
        return 0;
    }
    if (distance == step_length) {
        return 1;
    }
    if (distance < step_length) {
        return 2;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 3 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:5603,execs:3345,op:havoc,rep:2)
     */
    return (distance + step_length - 1) / step_length;
}

int main(void)
{
    long step_length;
    long distance;
    long result;

    printf("Enter jump length: ");
    if (scanf("%ld", &step_length) != 1) {
        fprintf(stderr, "Invalid input for jump length.\n");
        return EXIT_FAILURE;
    }

    printf("Enter target distance d: ");
    if (scanf("%ld", &distance) != 1) {
        fprintf(stderr, "Invalid input for distance.\n");
        return EXIT_FAILURE;
    }

    result = min_jumps(step_length, distance);
    if (result < 0) {
        fprintf(stderr, "Invalid values: jump length must be positive and distance non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of jumps required: %ld\n", result);
    return EXIT_SUCCESS;
}
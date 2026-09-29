#include <stdio.h>
#include <stdlib.h>

static long min_jumps(long jump_length, long distance)
{
    if (jump_length <= 0 || distance < 0)
    {
        return -1;
    }

    if (distance == 0)
    {
        return 0;
    }

    if (distance == jump_length)
    {
        return 1;
    }

    if (distance < jump_length)
    {
        return 2;
    }

    return (distance + jump_length - 1) / jump_length;
}

int main(void)
{
    long jump_length = 0;
    long distance = 0;
    long result = 0;

    printf("Enter jump length: ");
    if (scanf("%ld", &jump_length) != 1)
    {
        fprintf(stderr, "Error: invalid input for jump length\n");
        return EXIT_FAILURE;
    }

    printf("Enter target distance d: ");
    if (scanf("%ld", &distance) != 1)
    {
        fprintf(stderr, "Error: invalid input for distance\n");
        return EXIT_FAILURE;
    }

    result = min_jumps(jump_length, distance);
    if (result < 0)
    {
        fprintf(stderr, "Error: jump length must be positive and distance non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of jumps required: %ld\n", result);

    return EXIT_SUCCESS;
}
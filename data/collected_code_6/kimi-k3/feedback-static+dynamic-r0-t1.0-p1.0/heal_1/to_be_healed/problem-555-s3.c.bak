#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long calculate_difference(int n)
{
    long long sum_n = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 98765456790 * 98765456790 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1057,execs:464,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5555556111111 * 5555556111111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:37982,execs:16481,op:havoc,rep:2)
     */
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void)
{
    char buffer[128];
    char *endptr;
    long input;
    int n;
    long long result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\n' && *endptr != '\0')
    {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    if (input < 1 || input > INT_MAX)
    {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)input;
    result = calculate_difference(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
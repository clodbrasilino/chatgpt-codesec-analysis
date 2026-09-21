#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long calculate_difference(int n)
{
    long long sum = 0;
    long long sum_of_squares = 0;
    long long square_of_sum;
    long long difference;
    int i;

    if (n <= 0)
    {
        return 0;
    }

    for (i = 1; i <= n; i++)
    {
        sum += i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223371388520336796 + 9148307996689 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:392,execs:191,op:havoc,rep:1)
         */
        sum_of_squares += (long long)i * i;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7335330003 * 7335330003 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:891,execs:409,op:havoc,rep:2)
     * UBSan: signed integer overflow: 6172839660493828 * 6172839660493828 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:392,execs:191,op:havoc,rep:1)
     */
    square_of_sum = sum * sum;
    difference = square_of_sum - sum_of_squares;

    return difference;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *end_pointer;
    long parsed_value;
    int n;
    long long result;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtol(input_buffer, &end_pointer, 10);

    if (errno == ERANGE || parsed_value > INT_MAX || parsed_value < 0)
    {
        fprintf(stderr, "Error: Input out of valid range.\n");
        return EXIT_FAILURE;
    }

    if (end_pointer == input_buffer)
    {
        fprintf(stderr, "Error: No digits found in input.\n");
        return EXIT_FAILURE;
    }

    n = (int)parsed_value;

    result = calculate_difference(n);

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
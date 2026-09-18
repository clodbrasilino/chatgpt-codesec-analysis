#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_fourth_powers(int n)
{
    long long sum = 0;
    int i;

    if (n < 0)
    {
        return -1;
    }

    for (i = 1; i <= n; i++)
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:503,execs:244,op:havoc,rep:2)
         * UBSan: signed integer overflow: 167366136660029 * 55109 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:503,execs:244,op:havoc,rep:2)
         * UBSan: signed integer overflow: 9221330501411758027 + 5384089619838736 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:503,execs:244,op:havoc,rep:2)
         */
        sum += (long long)i * i * i * i;
    }

    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000012,time:36206,execs:15507,op:havoc,rep:2; likely memory-safety defect
  */

int main(void)
{
    char input[32];
    char *endptr;
    long value;
    int n;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(input, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < 0)
    {
        fprintf(stderr, "Error: Invalid input range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Error: Invalid input format\n");
        return EXIT_FAILURE;
    }

    n = (int)value;
    result = sum_of_fourth_powers(n);

    if (result < 0)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
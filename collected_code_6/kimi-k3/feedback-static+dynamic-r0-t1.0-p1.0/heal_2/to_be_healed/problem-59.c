#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int octagonal_number(int n, long long *result)
{
    if (result == NULL)
    {
        return -1;
    }

    if (n < 1)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:106,execs:94,op:havoc,rep:3)
     */
    if (n > (LLONG_MAX + 2LL) / 3LL)
    {
        return -1;
    }

    long long factor = 3LL * n - 2LL;

    if (n > LLONG_MAX / factor)
    {
        return -1;
    }

    long long value = (long long)n * factor;

    *result = value;
    return 0;
}

int main(void)
{
    int n;
    long long result;

    printf("Enter the value of n: ");

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (octagonal_number(n, &result) != 0)
    {
        fprintf(stderr, "Invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("The %dth octagonal number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}
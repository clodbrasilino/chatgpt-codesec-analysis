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

    /* Possible weaknesses found:
     *  Assuming that condition 'n<1' is not redundant
     */
    if (n < 1)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1793725781 * 5381177341 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:5991,execs:2741,op:havoc,rep:6)
     */
    long long value = (long long)n * (3LL * n - 2LL);

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'n>0' is always true
     */
    if (n > 0 && value / n != (3LL * n - 2LL))
    {
        return -1;
    }

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
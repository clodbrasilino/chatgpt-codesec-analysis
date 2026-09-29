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
     *  Assignment 'multiplier=3LL*n-2LL', assigned value is greater than 0
     */
    long long multiplier = 3LL * n - 2LL;
    
    /* Possible weaknesses found:
     *  Condition 'multiplier!=0' is always true
     *  Condition 'multiplier!=0' is always true [knownConditionTrueFalse]
     */
    if (multiplier != 0 && n > LLONG_MAX / multiplier)
    {
        return -1;
    }

    *result = (long long)n * multiplier;
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
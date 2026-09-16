#include <stdio.h>
#include <stdlib.h>

static long long int_sqrt(long long n)
{
    long long low;
    long long high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    long long mid;
    long long result;

    if (n < 0)
    {
        return -1;
    }

    low = 0;
    high = n;
    result = 0;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (mid <= n / (mid == 0 ? 1 : mid) && mid * mid <= n)
        {
            result = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}

static long long count_odd_factor_elements(long long low, long long high)
{
    long long sqrt_high;
    long long sqrt_low;

    if (low > high)
    {
        return 0;
    }

    if (high < 0)
    {
        return 0;
    }

    if (low < 0)
    {
        low = 0;
    }

    sqrt_high = int_sqrt(high);

    if (low == 0)
    {
        sqrt_low = -1;
    }
    else
    {
        sqrt_low = int_sqrt(low - 1);
    }

    if (sqrt_high < 0 || sqrt_low < -1)
    {
        return 0;
    }

    return sqrt_high - sqrt_low;
}

int main(void)
{
    long long low;
    long long high;
    long long result;
    int scan_status;

    printf("Enter the lower bound of the range: ");
    scan_status = scanf("%lld", &low);

    if (scan_status != 1)
    {
        fprintf(stderr, "Error: invalid input for lower bound.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the upper bound of the range: ");
    scan_status = scanf("%lld", &high);

    if (scan_status != 1)
    {
        fprintf(stderr, "Error: invalid input for upper bound.\n");
        return EXIT_FAILURE;
    }

    if (low > high)
    {
        fprintf(stderr, "Error: lower bound must not exceed upper bound.\n");
        return EXIT_FAILURE;
    }

    result = count_odd_factor_elements(low, high);

    printf("Number of elements with odd factors in range [%lld, %lld]: %lld\n",
           low, high, result);

    return EXIT_SUCCESS;
}
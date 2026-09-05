#include <stdio.h>
#include <limits.h>

long long sum_of_divisors(long long n)
{
    if (n <= 0)
    {
        return 0;
    }

    long long sum = 0;
    long long i = 1;

    /* Possible weaknesses found:
     *  Assuming that condition 'i<=n/i' is not redundant
     */
    while (i <= n / i)
    {
        if (n % i == 0)
        {
            /* Possible weaknesses found:
             *  pair is assigned 'n/i' here.
             */
            long long pair = n / i;
            /* Possible weaknesses found:
             *  Condition 'pair==i' is always false [knownConditionTrueFalse]
             *  Condition 'pair==i' is always false
             */
            if (pair == i)
            {
                sum += i;
            }
            else
            {
                sum += i + pair;
            }
        }
        i++;
    }

    return sum;
}

int main(void)
{
    long long num = 0;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &num) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (num <= 0)
    {
        fprintf(stderr, "Number must be positive\n");
        return 1;
    }

    long long result = sum_of_divisors(num);
    printf("Sum of divisors of %lld is %lld\n", num, result);

    return 0;
}
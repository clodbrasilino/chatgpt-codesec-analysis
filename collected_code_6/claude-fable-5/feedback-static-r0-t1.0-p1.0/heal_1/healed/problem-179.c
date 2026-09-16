#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static int count_digits(long long n)
{
    int count = 0;
    if (n == 0)
    {
        return 1;
    }
    while (n > 0)
    {
        count++;
        n /= 10;
    }
    return count;
}

static bool is_keith_number(long long n)
{
    long long terms[64] = {0};
    int num_digits;
    int i;
    long long temp;

    if (n < 10)
    {
        return false;
    }

    num_digits = count_digits(n);
    if (num_digits > 64)
    {
        return false;
    }

    temp = n;
    for (i = num_digits - 1; i >= 0; i--)
    {
        terms[i] = temp % 10;
        temp /= 10;
    }

    while (true)
    {
        long long next = 0;

        for (i = 0; i < num_digits; i++)
        {
            if (next > LLONG_MAX - terms[i])
            {
                return false;
            }
            next += terms[i];
        }

        if (next == n)
        {
            return true;
        }
        if (next > n)
        {
            return false;
        }

        for (i = 0; i < num_digits - 1; i++)
        {
            terms[i] = terms[i + 1];
        }
        terms[num_digits - 1] = next;
    }
}

int main(void)
{
    long long n;
    int result;

    printf("Enter a number: ");
    result = scanf("%lld", &n);
    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (n < 0)
    {
        fprintf(stderr, "Error: number must be non-negative\n");
        return 1;
    }

    if (is_keith_number(n))
    {
        printf("%lld is a Keith number\n", n);
    }
    else
    {
        printf("%lld is not a Keith number\n", n);
    }

    return 0;
}
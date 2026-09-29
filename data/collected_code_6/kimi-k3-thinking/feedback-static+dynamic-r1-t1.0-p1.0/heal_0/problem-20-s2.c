#include <stdio.h>
#include <limits.h>

int is_woodall(long long number);

int is_woodall(long long number)
{
    long long n;
    long long power_of_two;
    long long woodall;

    if (number < 1)
    {
        return 0;
    }

    power_of_two = 2;
    for (n = 1; n < LLONG_MAX; n++)
    {
        if (power_of_two > LLONG_MAX / n)
        {
            break;
        }

        woodall = n * power_of_two - 1;

        if (woodall == number)
        {
            return 1;
        }

        if (woodall > number)
        {
            break;
        }

        if (power_of_two > LLONG_MAX / 2)
        {
            break;
        }

        power_of_two *= 2;
    }

    return 0;
}

int main(void)
{
    long long number;

    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (is_woodall(number))
    {
        printf("%lld is a Woodall number.\n", number);
    }
    else
    {
        printf("%lld is not a Woodall number.\n", number);
    }

    return 0;
}
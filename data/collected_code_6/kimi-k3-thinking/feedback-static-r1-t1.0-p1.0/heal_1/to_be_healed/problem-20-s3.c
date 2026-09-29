#include <stdio.h>
#include <limits.h>

int is_woodall(unsigned long long num)
{
    unsigned long long n;
    /* Possible weaknesses found:
     *  The scope of the variable 'power' can be reduced. [variableScope]
     */
    unsigned long long power;
    /* Possible weaknesses found:
     *  The scope of the variable 'woodall' can be reduced. [variableScope]
     */
    unsigned long long woodall;

    for (n = 1; n < 64; n++)
    {
        power = 1ULL << n;
        if (power > ULLONG_MAX / n)
        {
            break;
        }
        woodall = power * n - 1;
        if (woodall == num)
        {
            return 1;
        }
        if (woodall > num)
        {
            break;
        }
    }
    return 0;
}

int main(void)
{
    unsigned long long num;

    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (is_woodall(num))
    {
        printf("%llu is a Woodall number.\n", num);
    }
    else
    {
        printf("%llu is not a Woodall number.\n", num);
    }

    return 0;
}
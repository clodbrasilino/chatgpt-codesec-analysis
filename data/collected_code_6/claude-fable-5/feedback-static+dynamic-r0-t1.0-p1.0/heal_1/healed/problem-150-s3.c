#include <stdio.h>
#include <stdbool.h>

static bool is_present(long long a, long long b, long long c)
{
    unsigned long long udiff;
    unsigned long long uc;

    if (c == 0)
    {
        return (b == a);
    }

    if (c > 0)
    {
        if (b < a)
        {
            return false;
        }
        udiff = (unsigned long long)b - (unsigned long long)a;
        uc = (unsigned long long)c;
    }
    else
    {
        if (b > a)
        {
            return false;
        }
        udiff = (unsigned long long)a - (unsigned long long)b;
        uc = -(unsigned long long)c;
    }

    return (udiff % uc == 0);
}

int main(void)
{
    long long a;
    long long b;
    long long c;

    printf("Enter first term (a): ");
    if (scanf("%lld", &a) != 1)
    {
        fprintf(stderr, "Invalid input for a\n");
        return 1;
    }

    printf("Enter number to search (b): ");
    if (scanf("%lld", &b) != 1)
    {
        fprintf(stderr, "Invalid input for b\n");
        return 1;
    }

    printf("Enter common difference (c): ");
    if (scanf("%lld", &c) != 1)
    {
        fprintf(stderr, "Invalid input for c\n");
        return 1;
    }

    if (is_present(a, b, c))
    {
        printf("%lld is present in the sequence\n", b);
    }
    else
    {
        printf("%lld is not present in the sequence\n", b);
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

static bool is_present(long long a, long long b, long long c)
{
    long long diff;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -3 - 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:12448,execs:8235,op:havoc,rep:6)
     */
    diff = b - a;

    if (c == 0)
    {
        return (diff == 0);
    }

    if (diff % c != 0)
    {
        return false;
    }

    return ((diff / c) >= 0);
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
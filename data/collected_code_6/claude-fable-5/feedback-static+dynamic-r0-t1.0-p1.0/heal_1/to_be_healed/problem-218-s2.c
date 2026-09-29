#include <stdio.h>
#include <stdlib.h>

long long min_operations(long long a, long long b);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 6
  */

long long min_operations(long long a, long long b)
{
    if (a == b)
    {
        return 0LL;
    }
    if (a > b)
    {
        return a - b;
    }
    return b - a;
}

int main(void)
{
    long long a = 0LL;
    long long b = 0LL;
    long long result = 0LL;

    printf("Enter the first number: ");
    if (scanf("%lld", &a) != 1)
    {
        fprintf(stderr, "Error: invalid input for the first number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second number: ");
    if (scanf("%lld", &b) != 1)
    {
        fprintf(stderr, "Error: invalid input for the second number.\n");
        return EXIT_FAILURE;
    }

    if ((a > 0LL && b < 0LL && a > (long long)9223372036854775807LL + b) ||
        (a < 0LL && b > 0LL && b > (long long)9223372036854775807LL + a))
    {
        fprintf(stderr, "Error: difference would overflow.\n");
        return EXIT_FAILURE;
    }

    result = min_operations(a, b);
    printf("Minimum operations required: %lld\n", result);

    return EXIT_SUCCESS;
}
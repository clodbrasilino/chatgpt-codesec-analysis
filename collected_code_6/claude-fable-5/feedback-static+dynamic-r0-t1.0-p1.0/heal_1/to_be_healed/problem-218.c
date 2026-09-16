#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 6
  */

static unsigned long long min_operations(long long a, long long b)
{
    unsigned long long ua;
    unsigned long long ub;

    ua = (unsigned long long)a;
    ub = (unsigned long long)b;

    if (a >= b) {
        return ua - ub;
    }
    return ub - ua;
}

int main(void)
{
    long long a;
    long long b;
    int result;

    printf("Enter first number: ");
    result = scanf("%lld", &a);
    if (result != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    result = scanf("%lld", &b);
    if (result != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    printf("Minimum operations required: %llu\n", min_operations(a, b));

    return EXIT_SUCCESS;
}
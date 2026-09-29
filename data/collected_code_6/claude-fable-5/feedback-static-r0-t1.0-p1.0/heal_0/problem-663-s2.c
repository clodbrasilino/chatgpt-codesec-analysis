#include <stdio.h>
#include <stdlib.h>

long long find_largest_k(long long x, long long y, long long n)
{
    if (x <= 0 || y < 0 || y >= x || y > n) {
        return -1;
    }
    return n - ((n - y) % x);
}

int main(void)
{
    long long x;
    long long y;
    long long n;
    long long result;

    printf("Enter x (divisor): ");
    if (scanf("%lld", &x) != 1) {
        fprintf(stderr, "Invalid input for x\n");
        return EXIT_FAILURE;
    }

    printf("Enter y (remainder): ");
    if (scanf("%lld", &y) != 1) {
        fprintf(stderr, "Invalid input for y\n");
        return EXIT_FAILURE;
    }

    printf("Enter n (upper bound): ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    result = find_largest_k(x, y, n);

    if (result < 0) {
        printf("No valid k exists for the given inputs.\n");
    } else {
        printf("Largest k such that k %% %lld == %lld and k <= %lld is: %lld\n",
               x, y, n, result);
    }

    return EXIT_SUCCESS;
}
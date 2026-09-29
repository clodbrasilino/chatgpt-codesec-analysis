#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long find_index_smallest_triangular(int n);

long long find_index_smallest_triangular(int n)
{
    long double limit;
    long double index;

    if (n < 1 || n > 18) {
        return -1;
    }

    if (n == 1) {
        return 1;
    }

    limit = powl(10.0L, (long double)(n - 1));
    index = ceill((sqrtl(8.0L * limit + 1.0L) - 1.0L) / 2.0L);

    if (index < 1.0L || index > 9.0e18L) {
        return -1;
    }

    return (long long)index;
}

int main(void)
{
    int n;
    long long result;

    printf("Enter number of digits: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = find_index_smallest_triangular(n);
    if (result < 0) {
        fprintf(stderr, "Error: n must be between 1 and 18\n");
        return EXIT_FAILURE;
    }

    printf("Index of smallest triangular number with %d digits: %lld\n", n, result);
    return EXIT_SUCCESS;
}
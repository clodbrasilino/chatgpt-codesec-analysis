#include <stdio.h>
#include <stdlib.h>

int count_divisors(int n);

int count_divisors(int n)
{
    int count = 0;
    int i;

    if (n == 0) {
        return 0;
    }

    if (n < 0) {
        if (n == -2147483647 - 1) {
            return 0;
        }
        n = -n;
    }

    for (i = 1; (long long)i * i <= (long long)n; i++) {
        if (n % i == 0) {
            count++;
            if (i != n / i) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    int n;
    int result;

    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = count_divisors(n);

    if (result == 0) {
        fprintf(stderr, "Error: divisor count is undefined for this input\n");
        return EXIT_FAILURE;
    }

    printf("Number of divisors of %d: %d\n", n, result);

    return EXIT_SUCCESS;
}
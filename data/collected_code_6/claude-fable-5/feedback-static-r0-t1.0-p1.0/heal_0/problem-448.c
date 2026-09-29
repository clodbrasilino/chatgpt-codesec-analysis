#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long perrin_sum(int n, int *error)
{
    long long a;
    long long b;
    long long c;
    long long sum;
    long long next;
    int i;

    *error = 0;

    if (n < 0) {
        *error = 1;
        return 0;
    }

    a = 3;
    b = 0;
    c = 2;
    sum = 0;

    if (n >= 1) {
        sum = a;
    }
    if (n >= 2) {
        sum += b;
    }
    if (n >= 3) {
        sum += c;
    }

    for (i = 3; i < n; i++) {
        if (a > LLONG_MAX - b) {
            *error = 2;
            return 0;
        }
        next = a + b;
        if (sum > LLONG_MAX - next) {
            *error = 2;
            return 0;
        }
        sum += next;
        a = b;
        b = c;
        c = next;
    }

    return sum;
}

int main(void)
{
    int n;
    int error;
    long long result;

    printf("Enter the number of Perrin terms to sum: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = perrin_sum(n, &error);

    if (error == 1) {
        fprintf(stderr, "Number of terms must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (error == 2) {
        fprintf(stderr, "Overflow detected for %d terms\n", n);
        return EXIT_FAILURE;
    }

    printf("Sum of the first %d Perrin numbers: %lld\n", n, result);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_series(int n)
{
    long long sum = 0;
    int current = n;

    while (current > 0) {
        sum += current;
        if (current < 2) {
            break;
        }
        current -= 2;
    }

    return sum;
}

int main(void)
{
    int n = 0;
    int result = 0;

    printf("Enter a positive integer: ");

    result = scanf("%d", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Error: input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("Sum: %lld\n", sum_series(n));

    return EXIT_SUCCESS;
}
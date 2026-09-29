#include <stdio.h>
#include <stdlib.h>

double average_of_odds(long n)
{
    long sum = 0;
    long count = 0;
    long i;

    for (i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }

    if (count == 0) {
        return 0.0;
    }

    return (double)sum / (double)count;
}

int main(void)
{
    long n;
    double result;

    printf("Enter an odd number: ");

    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Error: number must be positive\n");
        return EXIT_FAILURE;
    }

    if (n % 2 == 0) {
        fprintf(stderr, "Error: number must be odd\n");
        return EXIT_FAILURE;
    }

    result = average_of_odds(n);
    printf("Average of odd numbers up to %ld is %.2f\n", n, result);

    return EXIT_SUCCESS;
}
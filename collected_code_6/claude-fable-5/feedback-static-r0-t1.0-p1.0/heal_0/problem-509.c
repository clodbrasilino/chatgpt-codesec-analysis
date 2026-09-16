#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(long n, double *result)
{
    long count;
    long sum;
    long i;

    if (result == NULL) {
        return -1;
    }

    if (n < 1 || (n % 2L) == 0L) {
        return -1;
    }

    count = 0L;
    sum = 0L;

    for (i = 1L; i <= n; i += 2L) {
        sum += i;
        count++;
    }

    if (count == 0L) {
        return -1;
    }

    *result = (double)sum / (double)count;
    return 0;
}

int main(void)
{
    long n;
    double avg;
    int items;

    printf("Enter an odd number: ");

    items = scanf("%ld", &n);
    if (items != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (average_of_odds(n, &avg) != 0) {
        fprintf(stderr, "Input must be a positive odd number.\n");
        return EXIT_FAILURE;
    }

    printf("Average of odd numbers up to %ld is %.2f\n", n, avg);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

double average_of_evens(int n, int *status)
{
    if (n < 2 || (n % 2) != 0) {
        *status = -1;
        return 0.0;
    }

    long long sum = 0;
    long long count = 0;

    for (int i = 2; i <= n; i += 2) {
        sum += i;
        count++;
    }

    *status = 0;
    return (double)sum / (double)count;
}

int main(void)
{
    int n;
    int status;

    printf("Enter an even number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    double avg = average_of_evens(n, &status);
    if (status != 0) {
        fprintf(stderr, "Error: input must be a positive even number >= 2.\n");
        return EXIT_FAILURE;
    }

    printf("Average of even numbers up to %d is %.2f\n", n, avg);
    return EXIT_SUCCESS;
}
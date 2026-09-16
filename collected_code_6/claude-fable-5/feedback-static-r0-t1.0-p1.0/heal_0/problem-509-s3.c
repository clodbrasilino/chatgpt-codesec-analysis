#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n, int *status)
{
    int count = 0;
    long long sum = 0;
    int i;

    if (status == NULL) {
        return 0.0;
    }

    if (n <= 0 || (n % 2) == 0) {
        *status = -1;
        return 0.0;
    }

    for (i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }

    *status = 0;
    return (double)sum / (double)count;
}

int main(void)
{
    int n = 0;
    int status = 0;
    double result;

    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = average_of_odds(n, &status);
    if (status != 0) {
        fprintf(stderr, "Error: input must be a positive odd number.\n");
        return EXIT_FAILURE;
    }

    printf("Average of odd numbers till %d is %.2f\n", n, result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

double average_of_evens(int n, int *error)
{
    long long sum = 0;
    int count = 0;
    int i;

    if (error == NULL) {
        return 0.0;
    }

    if (n < 2 || (n % 2) != 0) {
        *error = 1;
        return 0.0;
    }

    for (i = 2; i <= n; i += 2) {
        sum += i;
        count++;
    }

    if (count == 0) {
        *error = 1;
        return 0.0;
    }

    *error = 0;
    return (double)sum / (double)count;
}

int main(void)
{
    int n = 0;
    int error = 0;
    double result;

    printf("Enter an even number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = average_of_evens(n, &error);
    if (error != 0) {
        fprintf(stderr, "Input must be a positive even number >= 2.\n");
        return EXIT_FAILURE;
    }

    printf("Average of even numbers up to %d is %.2f\n", n, result);
    return EXIT_SUCCESS;
}
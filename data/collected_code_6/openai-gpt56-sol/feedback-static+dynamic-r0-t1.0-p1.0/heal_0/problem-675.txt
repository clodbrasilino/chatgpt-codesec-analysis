#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int add_integers(int first, int second, int lower, int upper, int *result)
{
    long long sum;

    if (result == NULL || lower > upper) {
        return 0;
    }

    sum = (long long)first + (long long)second;

    if (sum >= lower && sum <= upper) {
        *result = 20;
        return 1;
    }

    if (sum < INT_MIN || sum > INT_MAX) {
        return 0;
    }

    *result = (int)sum;
    return 1;
}

int main(void)
{
    int first;
    int second;
    int lower;
    int upper;
    int result;

    if (scanf("%d %d %d %d", &first, &second, &lower, &upper) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!add_integers(first, second, lower, upper, &result)) {
        fputs("Unable to calculate result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
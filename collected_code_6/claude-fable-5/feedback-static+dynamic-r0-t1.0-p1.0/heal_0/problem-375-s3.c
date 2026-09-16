#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long round_to_nearest_multiple(long number, long multiple, int *error)
{
    if (multiple == 0) {
        *error = 1;
        return 0;
    }

    *error = 0;

    long abs_multiple = labs(multiple);
    long remainder = number % abs_multiple;

    if (remainder == 0) {
        return number;
    }

    long lower = number - remainder;
    long upper;

    if (number >= 0) {
        upper = lower + abs_multiple;
    } else {
        upper = lower;
        lower = upper - abs_multiple;
    }

    if (number - lower < upper - number) {
        return lower;
    }
    return upper;
}

int main(void)
{
    long number;
    long multiple;
    int error;

    printf("Enter the number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input for number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the multiple: ");
    if (scanf("%ld", &multiple) != 1) {
        fprintf(stderr, "Invalid input for multiple.\n");
        return EXIT_FAILURE;
    }

    long result = round_to_nearest_multiple(number, multiple, &error);

    if (error != 0) {
        fprintf(stderr, "Error: multiple cannot be zero.\n");
        return EXIT_FAILURE;
    }

    printf("%ld rounded to the nearest multiple of %ld is %ld\n",
           number, multiple, result);

    return EXIT_SUCCESS;
}
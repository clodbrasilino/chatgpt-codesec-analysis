#include <stdio.h>
#include <stdlib.h>

long round_to_nearest_multiple(long number, long multiple)
{
    long remainder;
    long half;

    if (multiple == 0) {
        return number;
    }

    if (multiple < 0) {
        multiple = -multiple;
    }

    remainder = number % multiple;

    if (remainder == 0) {
        return number;
    }

    half = multiple / 2;

    if (number >= 0) {
        if (remainder >= multiple - half) {
            return number + (multiple - remainder);
        }
        return number - remainder;
    }

    if (-remainder >= multiple - half) {
        return number - (multiple + remainder);
    }
    return number - remainder;
}

int main(void)
{
    long number;
    long multiple;
    long result;

    printf("Enter the number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input for number\n");
        return EXIT_FAILURE;
    }

    printf("Enter the multiple: ");
    if (scanf("%ld", &multiple) != 1) {
        fprintf(stderr, "Invalid input for multiple\n");
        return EXIT_FAILURE;
    }

    if (multiple == 0) {
        fprintf(stderr, "Multiple must not be zero\n");
        return EXIT_FAILURE;
    }

    result = round_to_nearest_multiple(number, multiple);

    printf("%ld rounded to the nearest multiple of %ld is %ld\n", number, multiple, result);

    return EXIT_SUCCESS;
}
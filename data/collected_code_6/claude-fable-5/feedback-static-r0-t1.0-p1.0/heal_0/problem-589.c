#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void find_perfect_squares(long low, long high);

void find_perfect_squares(long low, long high)
{
    long start;
    long i;
    int found = 0;

    if (low > high) {
        long temp = low;
        low = high;
        high = temp;
    }

    if (high < 0) {
        printf("No perfect squares in range [%ld, %ld]\n", low, high);
        return;
    }

    if (low < 0) {
        low = 0;
    }

    start = (long)floor(sqrt((double)low));
    while (start * start < low) {
        start++;
    }

    printf("Perfect squares between %ld and %ld:\n", low, high);
    for (i = start; i * i <= high; i++) {
        printf("%ld\n", i * i);
        found = 1;
    }

    if (!found) {
        printf("None found\n");
    }
}

int main(void)
{
    long low;
    long high;

    printf("Enter the lower bound: ");
    if (scanf("%ld", &low) != 1) {
        fprintf(stderr, "Invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    printf("Enter the upper bound: ");
    if (scanf("%ld", &high) != 1) {
        fprintf(stderr, "Invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    find_perfect_squares(low, high);

    return EXIT_SUCCESS;
}
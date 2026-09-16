#include <stdio.h>
#include <stdlib.h>

double trapezium_median(double base1, double base2)
{
    return (base1 + base2) / 2.0;
}

int main(void)
{
    double base1;
    double base2;
    double median;
    int result;

    printf("Enter the length of the first parallel side: ");
    result = scanf("%lf", &base1);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for first side.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the length of the second parallel side: ");
    result = scanf("%lf", &base2);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for second side.\n");
        return EXIT_FAILURE;
    }

    if (base1 <= 0.0 || base2 <= 0.0) {
        fprintf(stderr, "Error: side lengths must be positive.\n");
        return EXIT_FAILURE;
    }

    median = trapezium_median(base1, base2);

    printf("The median of the trapezium is: %.2f\n", median);

    return EXIT_SUCCESS;
}
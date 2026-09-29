#include <stdio.h>
#include <stdlib.h>

double dog_age_in_dog_years(double human_years)
{
    if (human_years < 0.0) {
        return -1.0;
    }

    if (human_years <= 2.0) {
        return human_years * 10.5;
    }

    return (2.0 * 10.5) + ((human_years - 2.0) * 4.0);
}

int main(void)
{
    double human_years = 0.0;
    double result = 0.0;
    int scan_status = 0;

    printf("Enter the dog's age in human years: ");

    scan_status = scanf("%lf", &human_years);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (human_years < 0.0 || human_years > 100.0) {
        fprintf(stderr, "Error: age must be between 0 and 100.\n");
        return EXIT_FAILURE;
    }

    result = dog_age_in_dog_years(human_years);
    if (result < 0.0) {
        fprintf(stderr, "Error: calculation failed.\n");
        return EXIT_FAILURE;
    }

    printf("The dog's age in dog years is: %.1f\n", result);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

double calculate_dog_years(double human_years)
{
    double dog_years;

    if (human_years < 0.0) {
        return -1.0;
    }

    if (human_years <= 2.0) {
        dog_years = human_years * 10.5;
    } else {
        dog_years = (2.0 * 10.5) + ((human_years - 2.0) * 4.0);
    }

    return dog_years;
}

int main(void)
{
    double human_years = 0.0;
    double dog_years = 0.0;
    int result;

    printf("Enter the dog's age in human years: ");

    result = scanf("%lf", &human_years);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (human_years < 0.0 || human_years > 100.0) {
        fprintf(stderr, "Error: age must be between 0 and 100.\n");
        return EXIT_FAILURE;
    }

    dog_years = calculate_dog_years(human_years);
    if (dog_years < 0.0) {
        fprintf(stderr, "Error: calculation failed.\n");
        return EXIT_FAILURE;
    }

    printf("The dog's age in dog years is: %.2f\n", dog_years);

    return EXIT_SUCCESS;
}
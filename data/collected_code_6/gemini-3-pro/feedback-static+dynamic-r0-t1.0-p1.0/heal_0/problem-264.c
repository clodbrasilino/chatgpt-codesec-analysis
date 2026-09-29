#include <stdio.h>
#include <stdlib.h>

double calculate_dog_years(double human_years) {
    if (human_years < 0.0) {
        return -1.0;
    }
    if (human_years <= 1.0) {
        return human_years * 15.0;
    }
    if (human_years <= 2.0) {
        return 15.0 + ((human_years - 1.0) * 9.0);
    }
    return 24.0 + ((human_years - 2.0) * 5.0);
}

int main(void) {
    double human_years = 0.0;
    double dog_years = 0.0;
    int scan_result = 0;

    printf("Enter dog's age in human years: ");
    scan_result = scanf("%lf", &human_years);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input format. Please enter a valid number.\n");
        return EXIT_FAILURE;
    }

    if (human_years < 0.0) {
        fprintf(stderr, "Error: Age cannot be negative.\n");
        return EXIT_FAILURE;
    }

    dog_years = calculate_dog_years(human_years);

    if (dog_years < 0.0) {
        fprintf(stderr, "Error: Calculation failed due to invalid internal state.\n");
        return EXIT_FAILURE;
    }

    printf("Dog's age in dog years: %.2f\n", dog_years);

    return EXIT_SUCCESS;
}
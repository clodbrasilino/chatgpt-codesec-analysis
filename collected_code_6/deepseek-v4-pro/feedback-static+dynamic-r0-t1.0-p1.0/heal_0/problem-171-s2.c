#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_pentagon_perimeter(const double side_length) {
    if (side_length <= 0.0) {
        return -1.0;
    }
    return 5.0 * side_length;
}

int main(void) {
    double side_length = 0.0;
    double perimeter = 0.0;
    int result = 0;

    printf("Enter the length of one side of the pentagon: ");
    result = scanf("%lf", &side_length);

    if (result != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_pentagon_perimeter(side_length);

    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Side length must be a positive number.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of the pentagon: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}
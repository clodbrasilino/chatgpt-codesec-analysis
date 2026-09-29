#include <stdio.h>
#include <stdbool.h>

float calculate_square_perimeter(float side_length) {
    if (side_length <= 0.0f) {
        return -1.0f;
    }
    return 4.0f * side_length;
}

int main(void) {
    float side;
    float perimeter;
    int scan_result;

    printf("Enter the side length of the square: ");
    scan_result = scanf("%f", &side);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a numeric value.\n");
        return 1;
    }

    perimeter = calculate_square_perimeter(side);

    if (perimeter < 0.0f) {
        fprintf(stderr, "Error: Side length must be a positive number.\n");
        return 1;
    }

    printf("The perimeter of the square is: %.2f\n", perimeter);

    return 0;
}
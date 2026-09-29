#include <stdio.h>
#include <stdlib.h>

double calculate_triangle_perimeter(double side_a, double side_b, double side_c) {
    if (side_a <= 0.0 || side_b <= 0.0 || side_c <= 0.0) {
        return -1.0;
    }
    
    if ((side_a + side_b <= side_c) || (side_a + side_c <= side_b) || (side_b + side_c <= side_a)) {
        return -1.0;
    }

    return side_a + side_b + side_c;
}

int main(void) {
    double a = 3.0;
    double b = 4.0;
    double c = 5.0;

    double perimeter = calculate_triangle_perimeter(a, b, c);

    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid triangle sides.\n");
        return EXIT_FAILURE;
    }

    printf("The perimeter of the triangle is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}
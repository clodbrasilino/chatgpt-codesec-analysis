#include <stdio.h>
#include <stdlib.h>

void find_focus_of_parabola(float a, float b, float c, float *focus_x, float *focus_y) {
    float vertex_x, focus_shift;
    vertex_x = -b / (2 * a);
    focus_shift = 1.0 / (4 * a);
    *focus_x = vertex_x;
    *focus_y = c - (b * b) / (4 * a) + focus_shift;
}

int main() {
    float a, b, c, focus_x, focus_y;
    
    printf("Enter coefficients a, b, and c of the parabola equation (y = ax^2 + bx + c): ");
    if (scanf("%f %f %f", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (a == 0) {
        fprintf(stderr, "Coefficient 'a' must be non-zero for a valid parabola.\n");
        return EXIT_FAILURE;
    }

    find_focus_of_parabola(a, b, c, &focus_x, &focus_y);
    printf("The focus of the parabola is at: (%.2f, %.2f)\n", focus_x, focus_y);
    return EXIT_SUCCESS;
}
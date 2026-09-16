#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool calculate_slope(double x1, double y1, double x2, double y2, double *slope);

bool calculate_slope(double x1, double y1, double x2, double y2, double *slope) {
    if (slope == NULL) {
        return false;
    }

    if (x1 == x2) {
        return false;
    }

    *slope = (y2 - y1) / (x2 - x1);
    
    return true;
}

int main(void) {
    double slope = 0.0;

    if (calculate_slope(1.0, 2.0, 5.0, 10.0, &slope)) {
        printf("Slope: %.2f\n", slope);
    } else {
        fprintf(stderr, "Error: Vertical line or invalid pointer.\n");
    }

    if (calculate_slope(3.0, 4.0, 3.0, 8.0, &slope)) {
        printf("Slope: %.2f\n", slope);
    } else {
        fprintf(stderr, "Error: Vertical line or invalid pointer.\n");
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) return 0;
    int count = 0;
    double max_x = ceil(radius);
    for (int x1 = -max_x; x1 <= max_x; x1++) {
        for (int y1 = -max_x; y1 <= max_x; y1++) {
            for (int x2 = x1; x2 <= max_x; x2++) {
                for (int y2 = y1; y2 <= max_x; y2++) {
                    if (sqrt(x1 * x1 + y1 * y1) <= radius && sqrt(x2 * x2 + y2 * y2) <= radius &&
                        sqrt(x1 * x1 + y2 * y2) <= radius && sqrt(x2 * x2 + y1 * y1) <= radius) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = count_rectangles_in_circle(radius);
    printf("Number of rectangles in the circle: %d\n", result);
    return EXIT_SUCCESS;
}
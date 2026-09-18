#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

long long count_rectangles_in_circle(double radius) {
    if (radius <= 0) return 0;
    long long count = 0;
    int64_t max_x = (int64_t)ceil(radius);
    for (int64_t x1 = -max_x; x1 <= max_x; x1++) {
        for (int64_t y1 = -max_x; y1 <= max_x; y1++) {
            for (int64_t x2 = x1; x2 <= max_x; x2++) {
                for (int64_t y2 = y1; y2 <= max_x; y2++) {
                    double dist1 = hypot((double)x1, (double)y1);
                    double dist2 = hypot((double)x2, (double)y2);
                    double dist3 = hypot((double)x1, (double)y2);
                    double dist4 = hypot((double)x2, (double)y1);
                    if (dist1 <= radius && dist2 <= radius && dist3 <= radius && dist4 <= radius) {
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
    long long result = count_rectangles_in_circle(radius);
    printf("Number of rectangles in the circle: %lld\n", result);
    return EXIT_SUCCESS;
}
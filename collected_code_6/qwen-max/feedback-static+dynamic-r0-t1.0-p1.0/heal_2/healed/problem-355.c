#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

int64_t countRectanglesInCircle(double r) {
    int64_t count = 0;
    for (int64_t y = 0; y <= (int64_t)r; ++y) {
        for (int64_t x = 0; x <= (int64_t)r; ++x) {
            if ((double)x * x + (double)y * y <= r * r) {
                count++;
            }
        }
    }
    return count * 4;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (radius < 0) {
        printf("Radius must be non-negative.\n");
        return 1;
    }

    int64_t rectangleCount = countRectanglesInCircle(radius);
    printf("The number of rectangles in the circle is: %lld\n", (long long)rectangleCount);
    return 0;
}
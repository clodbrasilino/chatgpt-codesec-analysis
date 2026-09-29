#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

int64_t countRectanglesInCircle(double r) {
    int64_t count = 0;
    /* Possible weaknesses found:
     * UBSan: 1e+25 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:56818,execs:344,op:havoc,rep:15)
     */
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
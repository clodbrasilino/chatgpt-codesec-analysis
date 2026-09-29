#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

long long count_rectangles_in_circle(double radius)
{
    long long count = 0;
    long long r_squared;
    long long x, y;
    
    if (radius < 0.0 || !isfinite(radius)) {
        errno = EDOM;
        return -1;
    }
    
    if (radius > sqrt((double)LLONG_MAX)) {
        errno = ERANGE;
        return -1;
    }
    
    r_squared = (long long)(radius * radius);
    
    for (x = 0; x <= (long long)radius; ++x) {
        for (y = 0; y <= (long long)radius; ++y) {
            if (x * x + y * y <= r_squared) {
                if (x == 0 && y == 0) {
                    count += 1;
                } else if (x == 0 || y == 0) {
                    count += 2;
                } else {
                    count += 4;
                }
            }
        }
    }
    
    return count;
}

int main(void)
{
    double radius;
    long long result;
    
    printf("Enter the radius: ");
    
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    result = count_rectangles_in_circle(radius);
    
    if (result == -1) {
        if (errno == EDOM) {
            fprintf(stderr, "Error: Invalid radius value\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Error: Radius value out of range\n");
        } else {
            fprintf(stderr, "Error: Unknown error occurred\n");
        }
        return 1;
    }
    
    printf("Number of rectangles in circle: %lld\n", result);
    
    return 0;
}
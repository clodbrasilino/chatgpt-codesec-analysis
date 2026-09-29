#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

int count_rectangles_in_circle(double radius, long long *count) {
    if (count == NULL) {
        return -1;
    }
    
    if (radius < 0.0 || !isfinite(radius)) {
        return -1;
    }
    
    *count = 0;
    
    if (radius == 0.0) {
        return 0;
    }
    
    double r_squared = radius * radius;
    long long r_floor = (long long)floor(radius);
    
    if (r_floor > LLONG_MAX / 4) {
        return -1;
    }
    
    for (long long i = 1; i <= r_floor; i++) {
        double i_sq = (double)(i * i);
        if (i_sq > r_squared) {
            break;
        }
        
        double remaining = r_squared - i_sq;
        if (remaining < 0.0) {
            remaining = 0.0;
        }
        
        double max_j = sqrt(remaining);
        long long j_max = (long long)floor(max_j);
        
        if (j_max > 0) {
            if (*count > LLONG_MAX - j_max) {
                return -1;
            }
            *count += j_max;
        }
    }
    
    if (*count > LLONG_MAX / 4) {
        return -1;
    }
    
    *count *= 4;
    
    return 0;
}

int main(void) {
    double radius;
    long long count;
    
    printf("Enter radius: ");
    
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (count_rectangles_in_circle(radius, &count) != 0) {
        fprintf(stderr, "Error calculating rectangles\n");
        return 1;
    }
    
    printf("Number of rectangles: %lld\n", count);
    
    return 0;
}
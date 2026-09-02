#include <stdio.h>
#include <math.h>

int count_rectangles_in_circle(double radius) {
    int count = 0;
    int r_int = (int)floor(radius);
    
    for (int x = 1; x <= r_int; x++) {
        for (int y = 1; y <= r_int; y++) {
            double diagonal = sqrt((double)x * x + (double)y * y);
            if (diagonal <= 2.0 * radius) {
                count++;
            }
        }
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    double radius;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (radius <= 0) {
        fprintf(stderr, "Radius must be positive\n");
        return 1;
    }
    
    int result = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", result);
    
    return 0;
}
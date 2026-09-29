#include <stdio.h>
#include <stdlib.h>

double max_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    if (radius == 0.0) {
        return 0.0;
    }
    return radius * radius;
}

int main(void) {
    double radius;
    
    if (scanf("%lf", &radius) != 1) {
        return EXIT_FAILURE;
    }
    
    if (radius < 0.0) {
        printf("-1\n");
        return EXIT_SUCCESS;
    }
    
    double area = max_triangle_area(radius);
    
    printf("%.4f\n", area);
    
    return EXIT_SUCCESS;
}
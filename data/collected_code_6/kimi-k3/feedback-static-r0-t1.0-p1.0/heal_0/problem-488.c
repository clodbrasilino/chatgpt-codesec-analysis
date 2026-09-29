#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

double calculate_pentagon_area(Point vertices[5]) {
    double area = 0.0;
    int i;
    
    if (vertices == NULL) {
        return -1.0;
    }
    
    for (i = 0; i < 5; i++) {
        int j = (i + 1) % 5;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    
    area = fabs(area) / 2.0;
    return area;
}

int main(void) {
    Point pentagon[5];
    double area;
    int i;
    
    printf("Enter the coordinates of 5 vertices (x y):\n");
    
    for (i = 0; i < 5; i++) {
        printf("Vertex %d: ", i + 1);
        if (scanf("%lf %lf", &pentagon[i].x, &pentagon[i].y) != 2) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }
    
    area = calculate_pentagon_area(pentagon);
    
    if (area < 0.0) {
        fprintf(stderr, "Error calculating area\n");
        return EXIT_FAILURE;
    }
    
    printf("Area of pentagon: %.2f\n", area);
    
    return EXIT_SUCCESS;
}
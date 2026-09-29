#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EPSILON 1e-10

typedef struct {
    double x;
    double y;
} Point;

bool is_linear(const Point *points, size_t count) {
    if (count < 2) {
        return true;
    }
    
    if (count == 2) {
        return true;
    }
    
    double dx = points[1].x - points[0].x;
    double dy = points[1].y - points[0].y;
    
    for (size_t i = 2; i < count; i++) {
        double current_dx = points[i].x - points[0].x;
        double current_dy = points[i].y - points[0].y;
        
        double cross_product = dx * current_dy - dy * current_dx;
        
        if (cross_product < -EPSILON || cross_product > EPSILON) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    size_t count;
    
    printf("Enter the number of points: ");
    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (count == 0) {
        printf("No points provided\n");
        return EXIT_FAILURE;
    }
    
    Point *points = malloc(count * sizeof(Point));
    if (points == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("Enter coordinates for point %zu (x y): ", i + 1);
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Invalid input\n");
            free(points);
            return EXIT_FAILURE;
        }
    }
    
    if (is_linear(points, count)) {
        printf("The points are collinear\n");
    } else {
        printf("The points are not collinear\n");
    }
    
    free(points);
    return EXIT_SUCCESS;
}
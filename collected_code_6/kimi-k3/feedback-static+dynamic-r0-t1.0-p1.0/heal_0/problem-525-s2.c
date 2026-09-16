#include <stdio.h>

typedef struct {
    double x1, y1, x2, y2;
} Line;

int are_parallel(Line l1, Line l2) {
    double dx1 = l1.x2 - l1.x1;
    double dy1 = l1.y2 - l1.y1;
    double dx2 = l2.x2 - l2.x1;
    double dy2 = l2.y2 - l2.y1;
    
    double cross = dx1 * dy2 - dy1 * dx2;
    return (cross >= -1e-9 && cross <= 1e-9);
}

int main(void) {
    Line line1, line2;
    
    printf("Enter line 1 (x1 y1 x2 y2): ");
    if (scanf("%lf %lf %lf %lf", &line1.x1, &line1.y1, &line1.x2, &line1.y2) != 4) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter line 2 (x1 y1 x2 y2): ");
    if (scanf("%lf %lf %lf %lf", &line2.x1, &line2.y1, &line2.x2, &line2.y2) != 4) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (are_parallel(line1, line2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }
    
    return 0;
}
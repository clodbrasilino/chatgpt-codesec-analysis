#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x1, y1, x2, y2;
} Line;

double get_slope(Line line) {
    if (line.x2 - line.x1 == 0.0) {
        return __DBL_MAX__;
    }
    return (line.y2 - line.y1) / (line.x2 - line.x1);
}

int are_parallel(Line line1, Line line2) {
    double slope1 = get_slope(line1);
    double slope2 = get_slope(line2);
    if (slope1 == __DBL_MAX__ && slope2 == __DBL_MAX__) {
        return 1;
    }
    if (slope1 == __DBL_MAX__ || slope2 == __DBL_MAX__) {
        return 0;
    }
    return slope1 == slope2;
}

int main(void) {
    Line line1, line2;
    printf("Enter coordinates for line 1 (x1 y1 x2 y2): ");
    if (scanf("%lf %lf %lf %lf", &line1.x1, &line1.y1, &line1.x2, &line1.y2) != 4) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Enter coordinates for line 2 (x1 y1 x2 y2): ");
    if (scanf("%lf %lf %lf %lf", &line2.x1, &line2.y1, &line2.x2, &line2.y2) != 4) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (line1.x1 == line1.x2 && line1.y1 == line1.y2) {
        fprintf(stderr, "Line 1 is degenerate.\n");
        return EXIT_FAILURE;
    }
    if (line2.x1 == line2.x2 && line2.y1 == line2.y2) {
        fprintf(stderr, "Line 2 is degenerate.\n");
        return EXIT_FAILURE;
    }
    if (are_parallel(line1, line2)) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }
    return EXIT_SUCCESS;
}
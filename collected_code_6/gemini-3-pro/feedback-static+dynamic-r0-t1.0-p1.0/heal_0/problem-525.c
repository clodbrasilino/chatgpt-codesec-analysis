#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Line;

int areLinesParallel(Line l1, Line l2) {
    double dx1 = l1.p2.x - l1.p1.x;
    double dy1 = l1.p2.y - l1.p1.y;
    double dx2 = l2.p2.x - l2.p1.x;
    double dy2 = l2.p2.y - l2.p1.y;

    if (fabs(dx1) < EPSILON && fabs(dx2) < EPSILON) {
        return 1;
    }

    if (fabs(dx1) < EPSILON || fabs(dx2) < EPSILON) {
        return 0;
    }

    double slope1 = dy1 / dx1;
    double slope2 = dy2 / dx2;

    if (fabs(slope1 - slope2) < EPSILON) {
        return 1;
    }

    return 0;
}

int main(void) {
    Line line1 = {{0.0, 0.0}, {2.0, 2.0}};
    Line line2 = {{1.0, 1.0}, {3.0, 3.0}};
    Line line3 = {{0.0, 0.0}, {2.0, 0.0}};
    Line line4 = {{0.0, 1.0}, {2.0, 5.0}};

    if (areLinesParallel(line1, line2)) {
        printf("Line 1 and Line 2 are parallel.\n");
    } else {
        printf("Line 1 and Line 2 are not parallel.\n");
    }

    if (areLinesParallel(line3, line4)) {
        printf("Line 3 and Line 4 are parallel.\n");
    } else {
        printf("Line 3 and Line 4 are not parallel.\n");
    }

    return 0;
}
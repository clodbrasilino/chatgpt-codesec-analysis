#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Line;

int are_parallel(Line l1, Line l2) {
    double dx1 = l1.p2.x - l1.p1.x;
    double dy1 = l1.p2.y - l1.p1.y;
    double dx2 = l2.p2.x - l2.p1.x;
    double dy2 = l2.p2.y - l2.p1.y;

    if (dx1 == 0.0 && dx2 == 0.0) {
        return 1;
    }

    if (dx1 == 0.0 || dx2 == 0.0) {
        return 0;
    }

    if ((dy1 * dx2) == (dy2 * dx1)) {
        return 1;
    }

    return 0;
}

int main(void) {
    Line l1 = {{0.0, 0.0}, {1.0, 1.0}};
    Line l2 = {{1.0, 1.0}, {2.0, 2.0}};
    Line l3 = {{0.0, 0.0}, {1.0, 0.0}};
    Line l4 = {{0.0, 5.0}, {0.0, 10.0}};
    Line l5 = {{0.0, 0.0}, {0.0, 1.0}};

    if (are_parallel(l1, l2)) {
        printf("l1 and l2 are parallel\n");
    } else {
        printf("l1 and l2 are not parallel\n");
    }

    if (are_parallel(l1, l3)) {
        printf("l1 and l3 are parallel\n");
    } else {
        printf("l1 and l3 are not parallel\n");
    }

    if (are_parallel(l4, l5)) {
        printf("l4 and l5 are parallel\n");
    } else {
        printf("l4 and l5 are not parallel\n");
    }

    return 0;
}
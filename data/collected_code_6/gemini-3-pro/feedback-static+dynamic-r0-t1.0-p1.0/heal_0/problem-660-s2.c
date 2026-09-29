#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Range;

bool has_overlap(Range r1, Range r2) {
    return (r1.start <= r2.end && r2.start <= r1.end);
}

int* choose_points(Range r1, Range r2) {
    int* points = (int*)malloc(2 * sizeof(int));
    if (!points) {
        return NULL;
    }

    if (has_overlap(r1, r2)) {
        free(points);
        return NULL;
    }

    points[0] = r1.start;
    points[1] = r2.start;

    return points;
}

int main(void) {
    Range r1 = {1, 5};
    Range r2 = {10, 15};
    Range r3 = {4, 12};

    int* points1 = choose_points(r1, r2);
    if (points1) {
        printf("%d %d\n", points1[0], points1[1]);
        free(points1);
    } else {
        printf("Ranges overlap or allocation failed.\n");
    }

    int* points2 = choose_points(r1, r3);
    if (points2) {
        printf("%d %d\n", points2[0], points2[1]);
        free(points2);
    } else {
        printf("Ranges overlap or allocation failed.\n");
    }

    return 0;
}
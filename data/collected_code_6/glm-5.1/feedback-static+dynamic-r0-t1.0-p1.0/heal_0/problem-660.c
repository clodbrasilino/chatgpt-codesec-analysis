#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    int point1;
    int point2;
} PointPair;

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int choose_non_overlapping_points(Range r1, Range r2, PointPair *result) {
    if (!result) {
        return -1;
    }

    if (r1.start > r1.end || r2.start > r2.end) {
        return -1;
    }

    int overlap_start = r1.start > r2.start ? r1.start : r2.start;
    int overlap_end = r1.end < r2.end ? r1.end : r2.end;

    if (overlap_start <= overlap_end) {
        return -1;
    }

    result->point1 = r1.start;
    result->point2 = r2.start;

    return 0;
}

int main() {
    Range r1 = {10, 20};
    Range r2 = {30, 40};
    PointPair result;

    if (choose_non_overlapping_points(r1, r2, &result) == 0) {
        printf("Point from range 1: %d\n", result.point1);
        printf("Point from range 2: %d\n", result.point2);
    } else {
        printf("Ranges overlap or are invalid.\n");
    }

    Range r3 = {5, 15};
    Range r4 = {10, 25};

    if (choose_non_overlapping_points(r3, r4, &result) == 0) {
        printf("Point from range 3: %d\n", result.point1);
        printf("Point from range 4: %d\n", result.point2);
    } else {
        printf("Ranges overlap or are invalid.\n");
    }

    Range r5 = {0, 0};

    if (choose_non_overlapping_points(r5, r5, &result) == 0) {
        printf("Point from range 5: %d\n", result.point1);
        printf("Point from range 5: %d\n", result.point2);
    } else {
        printf("Ranges overlap or are invalid.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int choose_points(Range *range1, Range *range2, int *point1, int *point2) {
    if (!range1 || !range2 || !point1 || !point2) {
        return -1;
    }
    if (range1->start > range1->end || range2->start > range2->end) {
        return -1;
    }

    if (range1->end < range2->start) {
        *point1 = range1->end;
        *point2 = range2->start;
        return 0;
    }
    if (range2->end < range1->start) {
        *point1 = range1->start;
        *point2 = range2->end;
        return 0;
    }

    if (range1->end < range2->end) {
        *point1 = range1->start;
        *point2 = range1->end + 1;
        if (*point2 <= range2->end) {
            return 0;
        }
    } else {
        *point1 = range2->end + 1;
        *point2 = range2->start;
        if (*point1 <= range1->end) {
            return 0;
        }
    }

    return -1;
}

int main(void) {
    Range r1 = {1, 5};
    Range r2 = {3, 8};
    int p1, p2;

    if (choose_points(&r1, &r2, &p1, &p2) == 0) {
        printf("%d %d\n", p1, p2);
    } else {
        printf("No valid points found\n");
    }

    Range r3 = {1, 3};
    Range r4 = {4, 6};

    if (choose_points(&r3, &r4, &p1, &p2) == 0) {
        printf("%d %d\n", p1, p2);
    } else {
        printf("No valid points found\n");
    }

    Range r5 = {10, 20};
    Range r6 = {5, 15};

    if (choose_points(&r5, &r6, &p1, &p2) == 0) {
        printf("%d %d\n", p1, p2);
    } else {
        printf("No valid points found\n");
    }

    Range r7 = {1, 1};
    Range r8 = {1, 1};

    if (choose_points(&r7, &r8, &p1, &p2) == 0) {
        printf("%d %d\n", p1, p2);
    } else {
        printf("No valid points found\n");
    }

    return 0;
}
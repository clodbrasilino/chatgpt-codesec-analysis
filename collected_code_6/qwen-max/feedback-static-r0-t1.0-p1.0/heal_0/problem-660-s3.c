#include <stdio.h>
#include <stdlib.h>

typedef struct Range {
    int start;
    int end;
} Range;

int isOverlap(Range r1, Range r2) {
    return (r1.start <= r2.end && r2.start <= r1.end);
}

void choosePoints(Range r1, Range r2, int *point1, int *point2) {
    if (!isOverlap(r1, r2)) {
        *point1 = r1.start;
        *point2 = r2.start;
    } else {
        *point1 = *point2 = -1; // Indicate overlap
    }
}

int main() {
    Range r1 = {10, 20};
    Range r2 = {30, 40};

    int point1, point2;
    choosePoints(r1, r2, &point1, &point2);

    if (point1 != -1 && point2 != -1) {
        printf("Point from first range: %d\n", point1);
        printf("Point from second range: %d\n", point2);
    } else {
        printf("The ranges overlap.\n");
    }

    return 0;
}
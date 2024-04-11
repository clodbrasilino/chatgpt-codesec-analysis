#include <stdio.h>

typedef struct {
    int a;
    int b;
    int c;
} Line;

int areParallel(Line l1, Line l2) {
    return (l1.a * l2.b - l2.a * l1.b) == 0;
}

int main() {
    Line line1 = {4, 2, 1};
    Line line2 = {2, 1, 3};
    Line line3 = {3, 2, 1};

    if (areParallel(line1, line2)) {
        printf("Line 1 and Line 2 are parallel.\n");
    } else {
        printf("Line 1 and Line 2 are not parallel.\n");
    }

    if (areParallel(line1, line3)) {
        printf("Line 1 and Line 3 are parallel.\n");
    } else {
        printf("Line 1 and Line 3 are not parallel.\n");
    }

    return 0;
}
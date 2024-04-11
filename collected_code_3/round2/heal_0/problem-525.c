#include <stdio.h>

typedef struct {
    int a;
    int b;
} Line;

int areParallel(Line l1, Line l2) {
    return l1.a * l2.b == l2.a * l1.b;
}

int main() {
    Line l1 = {4, 2};
    Line l2 = {2, 1};
    Line l3 = {3, 2};

    if (areParallel(l1, l2)) {
        printf("Line 1 and Line 2 are parallel.\n");
    } else {
        printf("Line 1 and Line 2 are not parallel.\n");
    }

    if (areParallel(l1, l3)) {
        printf("Line 1 and Line 3 are parallel.\n");
    } else {
        printf("Line 1 and Line 3 are not parallel.\n");
    }

    return 0;
}
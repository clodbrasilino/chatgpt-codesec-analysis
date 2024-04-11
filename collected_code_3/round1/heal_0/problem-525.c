#include <stdio.h>

typedef struct {
    int a;
    int b;
} Line;

int areParallel(Line l1, Line l2) {
    return l1.a * l2.b == l2.a * l1.b;
}

int main() {
    Line l1 = {2, 3};
    Line l2 = {4, 6};

    if (areParallel(l1, l2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }

    return 0;
}
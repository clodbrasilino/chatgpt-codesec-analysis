#include <stdio.h>

typedef struct {
    int a;
    int b;
    int c;
} Line;

int areParallel(Line l1, Line l2) {
    return (l1.a*l2.b == l2.a*l1.b);
}

int main() {
    Line line1 = {2, 3, 4};
    Line line2 = {4, 6, 8};

    if(areParallel(line1, line2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }

    return 0;
}
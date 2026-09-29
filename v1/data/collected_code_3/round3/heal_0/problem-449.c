#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Point;

bool isValidTriangle(Point p1, Point p2, Point p3) {
    int a = (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    return a != 0;
}

int main() {
    Point p1 = {0, 0}, p2 = {1, 1}, p3 = {2, 2};
    if(isValidTriangle(p1, p2, p3)) {
        printf("The points form a valid triangle.\n");
    } else {
        printf("The points do not form a valid triangle.\n");
    }
    return 0;
}
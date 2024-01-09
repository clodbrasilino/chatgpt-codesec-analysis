#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

int areParallel(Line line1, Line line2) {
    int dx1 = line1.end.x - line1.start.x;
    int dy1 = line1.end.y - line1.start.y;
    int dx2 = line2.end.x - line2.start.x;
    int dy2 = line2.end.y - line2.start.y;

    return dx1 * dy2 == dx2 * dy1;
}

int main() {
    Line line1;
    Line line2;

    line1.start.x = 1;
    line1.start.y = 2;
    line1.end.x = 3;
    line1.end.y = 4;

    line2.start.x = 5;
    line2.start.y = 6;
    line2.end.x = 7;
    line2.end.y = 8;

    if (areParallel(line1, line2)) {
        printf("The given lines are parallel.\n");
    } else {
        printf("The given lines are not parallel.\n");
    }

    return 0;
}
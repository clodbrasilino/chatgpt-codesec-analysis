#include <stdio.h>
#include <stdbool.h>

struct coordinates {
    int x;
    int y;
};

struct line {
    struct coordinates start;
    struct coordinates end;
};

bool check_parallel(struct line line1, struct line line2) {
    int line1_slope = (line1.end.y - line1.start.y) / (line1.end.x - line1.start.x);
    int line2_slope = (line2.end.y - line2.start.y) / (line2.end.x - line2.start.x);

    return line1_slope == line2_slope;
}

int main() {
    struct line line1 = {{1, 1}, {2, 2}};
    struct line line2 = {{2, 2}, {3, 3}};

    if (check_parallel(line1, line2))
        printf("Lines are parallel\n");
    else
        printf("Lines are not parallel\n");

    return 0;
}
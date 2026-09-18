#include <stdio.h>
#include <limits.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    if (side > 46340) {
        return -1;
    }
    return 4L * side * side;
}

int main() {
    int side;
    if (scanf("%d", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int area = lateral_surface_area(side);
    if (area == -1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d\n", area);
    return 0;
}
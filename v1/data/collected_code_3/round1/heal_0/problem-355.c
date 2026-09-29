#include <stdio.h>
#include <math.h>

int count_rectangles_in_circle(int r) {
    int diameter = 2 * r;
    int side = sqrt(2) * r;
    return (side * side);
}

int main() {
    int r;
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);
    int count = count_rectangles_in_circle(r);
    printf("Number of rectangles in the circle: %d\n", count);
    return 0;
}
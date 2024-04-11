#include <stdio.h>
#include <math.h>

int countRectanglesInCircle(int r) {
    int count = 0;
    int x, y;
    for (x = 1; x <= r; x++) {
        for (y = 1; y <= r; y++) {
            if (x * x + y * y <= r * r) {
                count += x * y;
            }
        }
    }
    return count;
}

int main() {
    int r;
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);
    int rectangles = countRectanglesInCircle(r);
    printf("Number of rectangles in a circle of radius %d is: %d\n", r, rectangles);
    return 0;
}
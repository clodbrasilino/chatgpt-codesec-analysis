#include <stdio.h>
#include <math.h>

int count_rectangles_in_circle(int r, int width, int height) {
    int diameter = 2 * r;
    int max_width = diameter / width;
    int max_height = diameter / height;
    return max_width * max_height;
}

int main() {
    int r = 10;
    int width = 2;
    int height = 3;
    int count = count_rectangles_in_circle(r, width, height);
    printf("Number of rectangles in a circle of radius %d: %d\n", r, count);
    return 0;
}
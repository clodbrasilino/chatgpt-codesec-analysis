#include <stdio.h>

typedef struct {
    float x;
    float y;
} Point;

float find_slope(Point p1, Point p2) {
    if(p2.x == p1.x) {
        printf("Error: Divide by zero! Points are vertically aligned.");
        return 0;
    }
    return (p2.y - p1.y) / (p2.x - p1.x);
}

int main() {
    Point p1 = {3, 2};
    Point p2 = {6, 4};
    float slope = find_slope(p1, p2);
    printf("The slope of the line is: %f\n", slope);
    return 0;
}
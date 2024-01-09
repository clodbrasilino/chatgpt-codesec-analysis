#include <stdio.h>

float findSlope(float x1, float y1, float x2, float y2) {
    return (y2 - y1) / (x2 - x1);
}

int main() {
    float x1, y1, x2, y2;
    printf("Enter the coordinates of two points on the line:\n");
    printf("Point 1 (x1, y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Point 2 (x2, y2): ");
    scanf("%f %f", &x2, &y2);

    float slope = findSlope(x1, y1, x2, y2);
    printf("The slope of the line is: %f\n", slope);

    return 0;
}
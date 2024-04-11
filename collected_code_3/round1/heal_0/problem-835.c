#include <stdio.h>

float find_slope(float x1, float y1, float x2, float y2) {
    return (y2 - y1) / (x2 - x1);
}

int main() {
    float x1, y1, x2, y2;
    printf("Enter coordinates of first point (x1, y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Enter coordinates of second point (x2, y2): ");
    scanf("%f %f", &x2, &y2);
    float slope = find_slope(x1, y1, x2, y2);
    printf("The slope of the line is: %.2f\n", slope);
    return 0;
}
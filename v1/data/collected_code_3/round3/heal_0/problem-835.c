#include <stdio.h>

float find_slope(float x1, float y1, float x2, float y2) {
    if(x1 == x2) {
        printf("Slope is undefined\n");
        return 0;
    }
    return (y2 - y1) / (x2 - x1);
}

int main() {
    float x1, y1, x2, y2;
    printf("Enter x1: ");
    scanf("%f", &x1);
    printf("Enter y1: ");
    scanf("%f", &y1);
    printf("Enter x2: ");
    scanf("%f", &x2);
    printf("Enter y2: ");
    scanf("%f", &y2);
    float slope = find_slope(x1, y1, x2, y2);
    printf("The slope of the line is: %.2f\n", slope);
    return 0;
}
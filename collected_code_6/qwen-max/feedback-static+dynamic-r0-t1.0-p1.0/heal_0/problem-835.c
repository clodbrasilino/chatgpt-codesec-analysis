#include <stdio.h>
#include <stdbool.h>

double find_slope(double x1, double y1, double x2, double y2) {
    if (x1 == x2) {
        return 0; // Assuming a large value or special value for vertical line
    }
    return (y2 - y1) / (x2 - x1);
}

int main() {
    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;
    double slope = find_slope(x1, y1, x2, y2);
    printf("The slope of the line is: %f\n", slope);
    return 0;
}
#include <stdio.h>
#include <math.h>

double getLargestTriangleInEllipse(double a, double b) {
    return a * b;
}

int main() {
    double a, b;

    printf("Enter the semi-major axis(A) of the ellipse: \n");
    scanf("%lf", &a);
    if (a <= 0) {
        printf("Semi-major axis(A) must be greater than 0.\n");
        return -1;
    }

    printf("Enter the semi-minor axis(B) of the ellipse: \n");
    scanf("%lf", &b);
    if (b <= 0) {
        printf("Semi-minor axis(B) must be greater than 0.\n");
        return -1;
    }

    double largestTriangleArea = getLargestTriangleInEllipse(a, b);
    printf("The largest triangle that can be inscribed in the ellipse is of area: %.3lf\n", largestTriangleArea);

    return 0;
}
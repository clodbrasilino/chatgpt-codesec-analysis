#include <stdio.h>
#include <math.h>

double findMedian(double a, double b, double h) {
    return 0.5 * (a + b) * h;
}

int main() {
    double a, b, h;
    printf("Enter the lengths of the parallel sides of the trapezium: ");
    scanf("%lf %lf", &a, &b);
    printf("Enter the height of the trapezium: ");
    scanf("%lf", &h);
    printf("The median of the trapezium is: %.2lf\n", findMedian(a, b, h));
    return 0;
}
#include <stdio.h>
#include <math.h>

double findMedian(double a, double b, double h) {
    return (a + b) / 2 * h;
}

int main() {
    double a, b, h;
    printf("Enter the lengths of the parallel sides and the height of the trapezium: ");
    scanf("%lf %lf %lf", &a, &b, &h);
    printf("The median of the trapezium is: %.2lf\n", findMedian(a, b, h));
    return 0;
}
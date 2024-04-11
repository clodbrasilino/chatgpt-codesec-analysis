#include <stdio.h>
#include <math.h>

double findMedian(double a, double b, double h) {
    return (a + b) / 2.0 * h;
}

int main() {
    double a, b, h;
    printf("Enter the lengths of the parallel sides and the height of the trapezium:\n");
    scanf("%lf %lf %lf", &a, &b, &h);
    double median = findMedian(a, b, h);
    printf("The median of the trapezium is: %.2lf\n", median);
    return 0;
}
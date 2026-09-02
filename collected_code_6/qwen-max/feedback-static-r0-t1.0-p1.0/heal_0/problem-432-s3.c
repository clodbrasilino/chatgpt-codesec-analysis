#include <stdio.h>
#include <stdlib.h>

double find_median(double a, double b, double c, double d) {
    if (a > c || b > d || a > d || c > b) {
        return -1.0;
    }
    double median = (b + c) / 2.0;
    return median;
}

int main() {
    double a = 5.0, b = 10.0, c = 7.0, d = 12.0;
    double median = find_median(a, b, c, d);
    if (median == -1.0) {
        printf("Invalid trapezium sides\n");
    } else {
        printf("Median of the trapezium: %f\n", median);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

double calculate_median(double b1, double b2, double h) {
    if (b1 < 0.0 || b2 < 0.0 || h < 0.0)
        return -1.0;
    return ((b1+b2)/2.0) * h;
}

int main() {
    double b1, b2, h, median;

    printf("Enter the value of base 1: ");
    if (scanf("%lf", &b1) != 1) {
        printf("Invalid input!");
        exit(1);
    }

    printf("Enter the value of base 2: ");
    if (scanf("%lf", &b2) != 1) {
        printf("Invalid input!");
        exit(1);
    }

    printf("Enter the value of height: ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input!");
        exit(1);
    }

    median = calculate_median(b1, b2, h);
    if (median == -1.0) {
        printf("Invalid value(s) entered. Bases and height cannot be negative.");
        exit(1);
    }

    printf("Median of trapezium is %lf\n", median);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

double calculateMedian(double b1, double b2, double h) {
    if(b1 < 0 || b2 < 0 || h < 0) {
        fprintf(stderr,"Error: Negative values are not allowed.");
        return -1;
    } 
    
    double median = (b1 + b2) / 2.0 * h;
    return median;
}

int main() {
    double base1, base2, height;
    printf("Enter the length of first base of the trapezium: ");
    scanf("%lf", &base1);
    printf("Enter the length of second base of the trapezium: ");
    scanf("%lf", &base2);
    printf("Enter the height of the trapezium: ");
    scanf("%lf", &height);
    
    double median = calculateMedian(base1, base2, height);
    
    if(median != -1) {
        printf("The median of the trapezium is: %.2f\n", median);
    } else {
        return EXIT_FAILURE;
    }

    return 0;
}
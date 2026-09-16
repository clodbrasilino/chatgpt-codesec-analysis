#include <stdio.h>
#include <math.h>

double calculate_pentagon_area(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    return (sqrt(5 * (5 + 2 * sqrt(5))) * side_length * side_length) / 4;
}

int main(void) {
    double side_length;
    double area;
    
    printf("Enter the side length of the pentagon: ");
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    area = calculate_pentagon_area(side_length);
    
    if (area < 0) {
        fprintf(stderr, "Invalid side length\n");
        return 1;
    }
    
    printf("Area of the pentagon: %.2f\n", area);
    
    return 0;
}
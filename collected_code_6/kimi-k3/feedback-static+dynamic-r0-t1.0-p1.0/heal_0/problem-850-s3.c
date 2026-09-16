#include <stdio.h>
#include <stdbool.h>

#define EPSILON 0.0001

bool isValidTriangle(double angle1, double angle2, double angle3) {
    if (angle1 <= 0.0 || angle2 <= 0.0 || angle3 <= 0.0) {
        return false;
    }
    
    double sum = angle1 + angle2 + angle3;
    double difference = sum - 180.0;
    
    if (difference < 0.0) {
        difference = -difference;
    }
    
    return difference < EPSILON;
}

int main(void) {
    double angle1, angle2, angle3;
    
    if (scanf("%lf %lf %lf", &angle1, &angle2, &angle3) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isValidTriangle(angle1, angle2, angle3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

double calculate_pentagon_perimeter(const double *sides, int count) {
    double perimeter = 0.0;
    
    if (sides == NULL || count != 5) {
        return -1.0;
    }
    
    for (int i = 0; i < count; i++) {
        if (sides[i] <= 0.0) {
            return -1.0;
        }
        perimeter += sides[i];
    }
    
    return perimeter;
}

int main(void) {
    double sides[5];
    double perimeter;
    
    printf("Enter the lengths of 5 sides of the pentagon:\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%lf", &sides[i]) != 1) {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
    }
    
    perimeter = calculate_pentagon_perimeter(sides, 5);
    
    if (perimeter < 0.0) {
        printf("Invalid side lengths. All sides must be positive.\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter of the pentagon: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}
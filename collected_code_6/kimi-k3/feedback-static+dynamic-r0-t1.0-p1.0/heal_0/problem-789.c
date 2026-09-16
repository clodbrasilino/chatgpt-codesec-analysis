#include <stdio.h>
#include <math.h>

double calculate_polygon_perimeter(int num_sides, double side_length);

int main(void) {
    int num_sides;
    double side_length;
    double perimeter;
    
    printf("Enter the number of sides: ");
    if (scanf("%d", &num_sides) != 1) {
        fprintf(stderr, "Invalid input for number of sides\n");
        return 1;
    }
    
    if (num_sides < 3) {
        fprintf(stderr, "A polygon must have at least 3 sides\n");
        return 1;
    }
    
    printf("Enter the side length: ");
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input for side length\n");
        return 1;
    }
    
    if (side_length <= 0.0) {
        fprintf(stderr, "Side length must be positive\n");
        return 1;
    }
    
    perimeter = calculate_polygon_perimeter(num_sides, side_length);
    printf("Perimeter of the regular polygon: %.2f\n", perimeter);
    
    return 0;
}

double calculate_polygon_perimeter(int num_sides, double side_length) {
    return num_sides * side_length;
}
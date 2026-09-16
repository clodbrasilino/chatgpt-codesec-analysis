#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static double calculate_perimeter(int sides, double side_length)
{
    return (double)sides * side_length;
}

int main(void)
{
    int sides;
    double side_length;
    double perimeter;
    int scan_result;
    
    printf("Enter the number of sides (minimum 3): ");
    scan_result = scanf("%d", &sides);
    
    if (scan_result != 1)
    {
        fprintf(stderr, "Error: Invalid input for number of sides\n");
        return EXIT_FAILURE;
    }
    
    if (sides < 3)
    {
        fprintf(stderr, "Error: A polygon must have at least 3 sides\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the length of each side: ");
    scan_result = scanf("%lf", &side_length);
    
    if (scan_result != 1)
    {
        fprintf(stderr, "Error: Invalid input for side length\n");
        return EXIT_FAILURE;
    }
    
    if (side_length <= 0.0)
    {
        fprintf(stderr, "Error: Side length must be positive\n");
        return EXIT_FAILURE;
    }
    
    if (side_length > 1e308 / (double)sides)
    {
        fprintf(stderr, "Error: Input values would cause overflow\n");
        return EXIT_FAILURE;
    }
    
    perimeter = calculate_perimeter(sides, side_length);
    
    if (isinf(perimeter) || isnan(perimeter))
    {
        fprintf(stderr, "Error: Calculation resulted in invalid value\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter of the regular polygon: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}
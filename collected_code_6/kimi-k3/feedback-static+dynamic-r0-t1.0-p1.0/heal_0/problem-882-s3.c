#include <stdio.h>
#include <math.h>
#include <errno.h>

double calculate_perimeter(double side_a, double side_b)
{
    if (side_a <= 0.0 || side_b <= 0.0 || isnan(side_a) || isnan(side_b) || isinf(side_a) || isinf(side_b))
    {
        errno = EINVAL;
        return -1.0;
    }
    
    return 2.0 * (side_a + side_b);
}

int main(void)
{
    double side_a;
    double side_b;
    double perimeter;
    
    printf("Enter length of side A: ");
    if (scanf("%lf", &side_a) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Enter length of side B: ");
    if (scanf("%lf", &side_b) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    perimeter = calculate_perimeter(side_a, side_b);
    
    if (perimeter < 0.0)
    {
        fprintf(stderr, "Error: Invalid side lengths\n");
        return 1;
    }
    
    printf("Perimeter: %.2f\n", perimeter);
    
    return 0;
}
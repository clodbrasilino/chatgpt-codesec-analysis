#include <stdio.h>
#include <math.h>

double find_third_side(double side1, double side2, char hypotenuse)
{
    double result = 0.0;
    
    if (side1 <= 0.0 || side2 <= 0.0)
    {
        return -1.0;
    }
    
    if (hypotenuse == 'h' || hypotenuse == 'H')
    {
        result = sqrt((side1 * side1) + (side2 * side2));
    }
    else if (hypotenuse == 's' || hypotenuse == 'S')
    {
        double larger = (side1 > side2) ? side1 : side2;
        double smaller = (side1 < side2) ? side1 : side2;
        
        if (larger <= smaller)
        {
            return -1.0;
        }
        
        result = sqrt((larger * larger) - (smaller * smaller));
    }
    else
    {
        return -1.0;
    }
    
    return result;
}

int main(void)
{
    double side1 = 0.0;
    double side2 = 0.0;
    char type = '\0';
    double result = 0.0;
    
    printf("Enter 'h' to find hypotenuse or 's' to find a side: ");
    
    if (scanf(" %c", &type) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Enter first side: ");
    
    if (scanf("%lf", &side1) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Enter second side: ");
    
    if (scanf("%lf", &side2) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    result = find_third_side(side1, side2, type);
    
    if (result < 0.0)
    {
        fprintf(stderr, "Error: Invalid triangle dimensions\n");
        return 1;
    }
    
    printf("Third side: %.2f\n", result);
    
    return 0;
}
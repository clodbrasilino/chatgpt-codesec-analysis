#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double find_third_side(double a, double b, bool is_hypotenuse)
{
    if (a <= 0.0 || b <= 0.0)
    {
        return -1.0;
    }
    
    if (is_hypotenuse)
    {
        if (b >= a)
        {
            return -1.0;
        }
        double result = sqrt((a * a) - (b * b));
        if (result <= 0.0)
        {
            return -1.0;
        }
        return result;
    }
    else
    {
        return sqrt((a * a) + (b * b));
    }
}

int main(void)
{
    double side1 = 0.0;
    double side2 = 0.0;
    int choice = 0;
    
    printf("Enter 1 to find hypotenuse, 0 to find a leg: ");
    if (scanf("%d", &choice) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (choice != 0 && choice != 1)
    {
        fprintf(stderr, "Invalid choice\n");
        return 1;
    }
    
    printf("Enter first side: ");
    if (scanf("%lf", &side1) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter second side: ");
    if (scanf("%lf", &side2) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    double result = find_third_side(side1, side2, choice == 1);
    
    if (result < 0.0)
    {
        fprintf(stderr, "Invalid triangle dimensions\n");
        return 1;
    }
    
    printf("Third side: %.2f\n", result);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

double find_trapezium_median(double base1, double base2)
{
    if (base1 < 0.0 || base2 < 0.0)
    {
        fprintf(stderr, "Error: Base lengths must be non-negative\n");
        return -1.0;
    }
    
    return (base1 + base2) / 2.0;
}

int main(void)
{
    double base1 = 0.0;
    double base2 = 0.0;
    double median = 0.0;
    int result = 0;
    
    printf("Enter the length of the first base: ");
    result = scanf("%lf", &base1);
    if (result != 1)
    {
        fprintf(stderr, "Error: Invalid input for first base\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the length of the second base: ");
    result = scanf("%lf", &base2);
    if (result != 1)
    {
        fprintf(stderr, "Error: Invalid input for second base\n");
        return EXIT_FAILURE;
    }
    
    median = find_trapezium_median(base1, base2);
    if (median < 0.0)
    {
        return EXIT_FAILURE;
    }
    
    printf("The median of the trapezium is: %.2f\n", median);
    
    return EXIT_SUCCESS;
}
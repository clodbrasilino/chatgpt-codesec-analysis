#include <stdio.h>

float trapezium_median(float a, float b, float h)
{
    return (a + b) / 2.0 * h;
}

int main()
{
    float a, b, h;
    
    printf("Enter the parallel side lengths (a and b): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%f%f", &a, &b);
    printf("Enter the height (h): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'h' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &h);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'h' is initialized [premium-bughuntingUninit]
     */
    float median = trapezium_median(a, b, h);
    
    printf("The median of the trapezium is: %.2f", median);
    
    return 0;
}
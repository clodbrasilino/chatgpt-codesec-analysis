#include <stdio.h>

// Function to calculate the perimeter of a rhombus
float findPerimeter(float side)
{
    // Perimeter of a rhombus is equal to 4 times the length of any side
    float perimeter = 4 * side;
    return perimeter;
}

int main()
{
    float side;
    printf("Enter the length of a side of the rhombus: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &side);

    // Call the function to find the perimeter
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    float perimeter = findPerimeter(side);

    printf("The perimeter of the rhombus is: %.2f\n", perimeter);
    return 0;
}
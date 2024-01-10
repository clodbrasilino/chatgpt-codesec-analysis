#include <stdio.h>

float findPerimeter(float side)
{
    float perimeter = 4 * side;
    return perimeter;
}

int main()
{
    float side = 0;

    printf("Enter the length of a side of the rhombus: ");
    scanf("%f", &side);

    float perimeter = findPerimeter(side);

    printf("The perimeter of the rhombus is: %.2f\n", perimeter);
    return 0;
}
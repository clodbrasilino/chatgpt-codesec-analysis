#include<stdio.h>

int findSquarePerimeter(int side)
{
    if(side <= 0)
    {
        printf("Side length of a square cannot be less than or equal to zero\n");
        return -1;
    }
    return 4 * side;
}

int main()
{
    int side, perimeter;

    printf("Enter the length of the side of the square: ");
    scanf("%d", &side);

    perimeter = findSquarePerimeter(side);

    if(perimeter != -1)
    {
        printf("The perimeter of the square is %d\n", perimeter);
    }

    return 0;
}
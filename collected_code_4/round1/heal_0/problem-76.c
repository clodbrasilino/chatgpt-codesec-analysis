#include <stdio.h>
#include <stdlib.h>

int countSquaresInRectangle(int length, int width) {
    int i, j;
    int count = 0;

    for(i = 1; i <= length; i++)
    {
        for(j = 1; j <= width; j++)
        {
            if(i > j)
            {
                count += (width - i + 1) * (length - i + 1);
            }
            else
            {
                count += (width - j + 1) * (length - j + 1);
            }
        }
    }

    return count;
}

int main() {
    int length, width;

    printf("Enter the length of the rectangle: ");
    scanf("%d", &length);
    if(length <= 0) {
        printf("Error: Length must be greater than 0\n");
        return EXIT_FAILURE;
    }

    printf("Enter the width of the rectangle: ");
    scanf("%d", &width);
    if(width <= 0) {
        printf("Error: Width must be greater than 0\n");
        return EXIT_FAILURE;
    }

    printf("The number of squares in the rectangle is: %d\n", countSquaresInRectangle(length, width));

    return EXIT_SUCCESS;
}
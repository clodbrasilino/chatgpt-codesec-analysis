#include <stdio.h>

float rectanglePerimeter(float length, float width);

int main(void)
{
    float length = 0.0f;
    float width = 0.0f;
    float perimeter = 0.0f;
    int scanResult = 0;

    printf("Enter length and width: ");
    scanResult = scanf("%f %f", &length, &width);

    if (scanResult == 2 && length >= 0.0f && width >= 0.0f)
    {
        perimeter = rectanglePerimeter(length, width);
        printf("Perimeter: %.2f\n", perimeter);
    }
    else
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    return 0;
}

float rectanglePerimeter(float length, float width)
{
    return 2.0f * (length + width);
}
#include<stdio.h>

float calculateDiscriminant(float a, float b, float c);

int main()
{
    float a, b, c, discriminant;

    printf("Enter the values of a, b, and c: ");
    scanf("%f %f %f", &a, &b, &c);

    discriminant = calculateDiscriminant(a, b, c);

    printf("The discriminant value is: %.2f\n", discriminant);

    return 0;
}

float calculateDiscriminant(float a, float b, float c)
{
    float discriminant;

    discriminant = (b * b) - (4 * a * c);

    return discriminant;
}
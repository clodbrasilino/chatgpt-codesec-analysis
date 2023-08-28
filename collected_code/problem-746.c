#include<stdio.h>

float findAreaOfSector(float radius, float angle)
{
    float area;

    area = (angle / 360) * 3.1416 * radius * radius;

    return area;
}

int main()
{
    float radius, angle, sectorArea;

    printf("Enter the radius of the sector: ");
    scanf("%f", &radius);

    printf("Enter the angle of the sector: ");
    scanf("%f", &angle);

    sectorArea = findAreaOfSector(radius, angle);

    printf("The area of the sector is: %.2f\n", sectorArea);

    return 0;
}
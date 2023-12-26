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
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);

    printf("Enter the angle of the sector: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'angle' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &angle);

    /* Possible weaknesses found:
     *  Cannot determine that 'angle' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    sectorArea = findAreaOfSector(radius, angle);

    printf("The area of the sector is: %.2f\n", sectorArea);

    return 0;
}
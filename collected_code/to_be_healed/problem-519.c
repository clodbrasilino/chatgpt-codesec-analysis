#include<stdio.h>
#include<math.h>

float calculateTetrahedronVolume(float sideLength)
{
    float volume;
    volume = (sqrt(2) / 12) * pow(sideLength, 3);
    return volume;
}

int main()
{
    float sideLength;
    printf("Enter the length of the side of the tetrahedron: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sideLength' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &sideLength);
    /* Possible weaknesses found:
     *  Cannot determine that 'sideLength' is initialized [premium-bughuntingUninit]
     */
    float volume = calculateTetrahedronVolume(sideLength);
    printf("Volume of the tetrahedron: %.2f\n", volume);
    return 0;
}
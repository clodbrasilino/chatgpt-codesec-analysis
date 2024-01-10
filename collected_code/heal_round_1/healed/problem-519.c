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
    float sideLength = 0.0;
    printf("Enter the length of the side of the tetrahedron: ");
    scanf("%f", &sideLength);

    if(sideLength > 0){
       float volume = calculateTetrahedronVolume(sideLength);
       printf("Volume of the tetrahedron: %.2f\n", volume);
    } else {
       printf("Error: Side length must be a positive number.\n");
    }

    return 0;
}
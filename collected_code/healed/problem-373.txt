#include <stdio.h>

float findVolume(float length, float width, float height) {
    float volume = length * width * height;
    return volume;
}

int main() {
    float length = 0.0, width = 0.0, height = 0.0, volume = 0.0;
    
    printf("Enter the length of the cuboid: ");
    scanf("%f", &length);
    
    printf("Enter the width of the cuboid: ");
    scanf("%f", &width);
    
    printf("Enter the height of the cuboid: ");
    scanf("%f", &height);
    
    volume = findVolume(length, width, height);
    printf("The volume of the cuboid is: %f\n", volume);
    
    return 0;
}
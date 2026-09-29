#include <stdio.h>

float findVolume(float length, float width, float height) {
    float volume = length * width * height;
    return volume;
}

int main() {
    float length, width, height, volume;
    
    printf("Enter the length of the cuboid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &length);
    
    printf("Enter the width of the cuboid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'width' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &width);
    
    printf("Enter the height of the cuboid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &height);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'width' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     */
    volume = findVolume(length, width, height);
    printf("The volume of the cuboid is: %f\n", volume);
    
    return 0;
}
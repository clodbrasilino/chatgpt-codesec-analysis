#include <stdio.h>

float findVolume(float base, float height, float depth) {
    float volume = 0.5 * base * height * depth;
    return volume;
}

int main() {
    float base, height, depth, volume;
    
    printf("Enter the base of the triangular prism: ");
    scanf("%f", &base);
    
    printf("Enter the height of the triangular prism: ");
    scanf("%f", &height);
    
    printf("Enter the depth of the triangular prism: ");
    scanf("%f", &depth);
    
    volume = findVolume(base, height, depth);
    printf("Volume of the triangular prism is: %.2f\n", volume);
    
    return 0;
}
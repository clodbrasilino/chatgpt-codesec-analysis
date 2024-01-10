#include <stdio.h>

float findVolume(float base, float height, float depth);

int main() {
    float base, height, depth, volume;
    
    printf("Enter the base of the triangular prism: ");
    if (scanf("%f", &base) != 1){
        printf("Invalid input for base, program will exit.\n");
        return 1;
    }
    
    printf("Enter the height of the triangular prism: ");
    if (scanf("%f", &height) != 1){
        printf("Invalid input for height, program will exit.\n");
        return 1;
    }
    
    printf("Enter the depth of the triangular prism: ");
    if (scanf("%f", &depth) != 1){
        printf("Invalid input for depth, program will exit.\n");
        return 1;
    }
    
    volume = findVolume(base, height, depth);
    printf("Volume of the triangular prism is: %.2f\n", volume);
    
    return 0;
}

float findVolume(float base, float height, float depth) {
    float volume = 0.5 * base * height * depth;
    return volume;
}
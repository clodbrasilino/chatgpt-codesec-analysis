#include <stdio.h>

float volume_of_triangular_prism(float base, float height, float length) {
    return 0.5 * base * height * length;
}

int main() {
    float base, height, length, volume;

    printf("Enter base of the triangular prism: ");
    scanf("%f", &base);

    printf("Enter height of the triangular prism: ");
    scanf("%f", &height);

    printf("Enter length of the triangular prism: ");
    scanf("%f", &length);

    volume = volume_of_triangular_prism(base, height, length);

    printf("Volume of the triangular prism is: %.2f\n", volume);

    return 0;
}
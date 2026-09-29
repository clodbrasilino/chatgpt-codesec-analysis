#include<stdio.h>

float find_surface_area(float height, float width, float length) {
    if ((height <= 0) || (width <= 0) || (length <= 0)) {
        printf("All dimensions must be greater than zero\n");
        return -1;
    }

    float surface_area = 2*(length*height + width*height);
    return surface_area;
}

int main() {
    float height, width, length;
    printf("Enter height of the cuboid:\n");
    scanf("%f", &height);
    printf("Enter width of the cuboid:\n");
    scanf("%f", &width);
    printf("Enter length of the cuboid:\n");
    scanf("%f", &length);
    float result = find_surface_area(height, width, length);
    
    if (result != -1) {
        printf("The lateral surface area of the cuboid is %.2f\n", result);
    }

    return 0;
}
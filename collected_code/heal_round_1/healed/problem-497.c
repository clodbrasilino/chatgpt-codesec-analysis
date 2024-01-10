#include <stdio.h>
#include <math.h>

float find_surface_area(float radius, float height) {
    const float PI = 3.14159;
    float slant_height = sqrt((radius * radius) + (height * height));
    float base_area = PI * (radius * radius);
    float lateral_area = PI * radius * slant_height;
    float surface_area = base_area + lateral_area;
    return surface_area;
}

int main() {
    float radius, height;

    printf("Enter the radius of the cone: ");
    scanf("%f", &radius);
    printf("Enter the height of the cone: ");
    scanf("%f", &height);

    float area = find_surface_area(radius, height);
    printf("Surface area of the cone: %f\n", area);

    return 0;
}
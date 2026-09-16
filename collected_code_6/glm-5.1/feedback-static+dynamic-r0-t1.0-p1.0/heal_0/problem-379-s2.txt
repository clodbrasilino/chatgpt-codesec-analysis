#include <stdio.h>

float calculate_surface_area(float length, float width, float height) {
    if (length <= 0.0f || width <= 0.0f || height <= 0.0f) {
        return -1.0f;
    }
    return 2.0f * (length * width + width * height + height * length);
}

int main() {
    float l = 2.0f;
    float w = 3.0f;
    float h = 4.0f;
    float area = calculate_surface_area(l, w, h);
    if (area < 0.0f) {
        return 1;
    }
    printf("%f\n", area);
    return 0;
}
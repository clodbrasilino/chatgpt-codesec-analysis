#include <stdio.h>

float calculate_trapezium_area(float base1, float base2, float height) {
    if (height < 0.0f) {
        return -1.0f;
    }
    if (base1 < 0.0f || base2 < 0.0f) {
        return -1.0f;
    }
    return ((base1 + base2) * height) / 2.0f;
}

int main() {
    float b1 = 8.0f;
    float b2 = 5.0f;
    float h = 6.0f;
    float area = calculate_trapezium_area(b1, b2, h);
    printf("%.2f\n", area);
    return 0;
}
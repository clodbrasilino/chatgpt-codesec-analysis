#include <stdio.h>

float triangle_perimeter(float a, float b, float c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return -1.0f;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return -1.0f;
    }
    return a + b + c;
}

int main(void) {
    float a, b, c;
    if (scanf("%f %f %f", &a, &b, &c) != 3) {
        return 1;
    }
    float result = triangle_perimeter(a, b, c);
    if (result < 0) {
        return 1;
    }
    printf("%f\n", result);
    return 0;
}
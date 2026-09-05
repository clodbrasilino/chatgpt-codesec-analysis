#include <stdio.h>

float calculate_perimeter(float a, float b, float c) {
    return a + b + c;
}

int main(void) {
    float a, b, c;

    if (scanf("%f %f %f", &a, &b, &c) != 3) {
        return 1;
    }

    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }

    if (a + b <= c || a + c <= b || b + c <= a) {
        return 1;
    }

    float perimeter = calculate_perimeter(a, b, c);
    printf("%.2f\n", perimeter);

    return 0;
}
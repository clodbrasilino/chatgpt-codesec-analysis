#include <stdio.h>

float area_of_rectangle(float length, float width) {
    return length * width;
}

int main() {
    float length = 5.0f;
    float width = 3.0f;
    float area = area_of_rectangle(length, width);
    printf("Area of the rectangle is: %f\n", area);
    return 0;
}
#include <stdio.h>

float rectangle_perimeter(float length, float width) {
    return 2 * (length + width);
}

int main(void) {
    float length = 5.0f;
    float width = 3.0f;
    float perimeter = rectangle_perimeter(length, width);
    
    printf("Perimeter: %.2f\n", perimeter);
    
    return 0;
}
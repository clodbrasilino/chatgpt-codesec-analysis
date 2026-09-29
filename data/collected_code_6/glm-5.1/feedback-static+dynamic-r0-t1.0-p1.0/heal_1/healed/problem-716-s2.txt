#include <stdio.h>

float find_rhombus_perimeter(float side) {
    if (side < 0.0f) {
        return -1.0f;
    }
    return 4.0f * side;
}

int main(void) {
    float side1 = 10.0f;
    float side2 = 5.0f;
    float side3 = 4.0f;
    
    float perimeter1 = find_rhombus_perimeter(side1);
    float perimeter2 = find_rhombus_perimeter(side2);
    float perimeter3 = find_rhombus_perimeter(side3);

    if (perimeter1 >= 0.0f) {
        printf("%.0f\n", perimeter1);
    }
    if (perimeter2 >= 0.0f) {
        printf("%.0f\n", perimeter2);
    }
    if (perimeter3 >= 0.0f) {
        printf("%.0f\n", perimeter3);
    }

    return 0;
}
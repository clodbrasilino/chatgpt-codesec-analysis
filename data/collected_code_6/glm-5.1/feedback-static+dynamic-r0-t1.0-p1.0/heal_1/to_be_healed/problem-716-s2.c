#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 20, got <no output>
  *  test case 0 failed: expected 40, got <no output>
  *  test case 2 failed: expected 16, got <no output>
  */

float find_rhombus_perimeter(float side) {
    float perimeter = 0.0f;
    if (side < 0.0f) {
        return -1.0f;
    }
    perimeter = 4.0f * side;
    if (perimeter < 0.0f) {
        return -1.0f;
    }
    return perimeter;
}

int main(void) {
    float side = 5.0f;
    float perimeter = find_rhombus_perimeter(side);
    if (perimeter < 0.0f) {
        return 1;
    }
    printf("%f\n", perimeter);
    return 0;
}
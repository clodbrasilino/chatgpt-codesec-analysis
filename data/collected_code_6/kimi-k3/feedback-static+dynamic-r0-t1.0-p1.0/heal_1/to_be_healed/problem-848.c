#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 700, got <no output>
  *  test case 1 failed: expected 450, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  */

float areaOfTrapezium(float base1, float base2, float height) {
    return 0.5 * (base1 + base2) * height;
}

int main() {
    float base1, base2, height;

    printf("Enter the lengths of the two bases and the height of the trapezium: ");
    scanf("%f %f %f", &base1, &base2, &height);

    if (base1 < 0 || base2 < 0 || height < 0) {
        printf("Error: All lengths must be non-negative.\n");
        return 1;
    }

    float area = areaOfTrapezium(base1, base2, height);
    printf("The area of the trapezium is: %.2f\n", area);

    return 0;
}
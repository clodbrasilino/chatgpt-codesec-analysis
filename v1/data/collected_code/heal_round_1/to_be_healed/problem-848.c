#include <stdio.h>

float findArea(float a, float b, float h) {
    float area = ((a + b) / 2) * h;
    return area;
}

int main() {
    float a, b, h;
    printf("Enter the length of the parallel side a: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &a);
    printf("Enter the length of the parallel side b: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &b);
    printf("Enter the height of the trapezium: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'h' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &h);
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'h' is initialized [premium-bughuntingUninit]
     */
    float result = findArea(a, b, h);
    printf("The area of the trapezium is: %.2f\n", result);
    return 0;
}
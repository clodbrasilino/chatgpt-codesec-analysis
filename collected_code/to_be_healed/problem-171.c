#include<stdio.h>

float calculatePerimeter(float side) {
    return 5 * side;
}

int main() {
    float side;
    printf("Enter the length of the side of the pentagon: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &side);
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    float perimeter = calculatePerimeter(side);
    printf("The perimeter of the pentagon is %.2f\n", perimeter);
    return 0;
}
#include <stdio.h>

int countSolutions(float a, float b, float c) {
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        return 2;
    } else if (discriminant == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    float a, b, c;
    printf("Enter the coefficients of the quadratic equation: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f %f", &a, &b, &c);

    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    int solutions = countSolutions(a, b, c);
    printf("Number of solutions: %d", solutions);

    return 0;
}
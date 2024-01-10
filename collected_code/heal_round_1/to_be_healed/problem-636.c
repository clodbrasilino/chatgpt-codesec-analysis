#include <stdio.h>
#include <math.h>

int checkReciprocalRoots(float a, float b, float c) {
    float discriminant, root1, root2;

    // Calculate the discriminant
    discriminant = b * b - 4 * a * c;

    // If the discriminant is less than 0, the roots are imaginary
    if (discriminant < 0) {
        return 0;
    }

    // Calculate the roots
    root1 = (-b + sqrt(discriminant)) / (2 * a);
    root2 = (-b - sqrt(discriminant)) / (2 * a);

    // Check if the roots are reciprocals of each other
    if (root1 * root2 == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    float a, b, c;

    printf("Enter the coefficients (a, b, c): ");
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
    if (checkReciprocalRoots(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return 0;
}
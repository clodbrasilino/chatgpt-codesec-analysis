#include <stdio.h>
#include <math.h>

int checkReciprocalRoots(float a, float b, float c) {
    float discriminant, root1, root2;

    discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0;
    }

    root1 = (-b + sqrt(discriminant)) / (2 * a);
    root2 = (-b - sqrt(discriminant)) / (2 * a);

    if (root1 * root2 == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    float a = 0.0, b = 0.0, c = 0.0;

    printf("Enter the coefficients (a, b, c): ");
    scanf("%f %f %f", &a, &b, &c);

    if (checkReciprocalRoots(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return 0;
}
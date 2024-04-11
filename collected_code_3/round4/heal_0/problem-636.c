#include <stdio.h>
#include <math.h>

int checkReciprocalRoots(float a, float b, float c) {
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return 0;
    }
    float root1 = (-b + sqrt(discriminant)) / (2*a);
    float root2 = (-b - sqrt(discriminant)) / (2*a);
    if (root1 == 1/root2 || root2 == 1/root1) {
        return 1;
    }
    return 0;
}

int main() {
    float a, b, c;
    printf("Enter coefficients a, b and c: ");
    scanf("%f %f %f",&a, &b, &c);
    if (checkReciprocalRoots(a, b, c)) {
        printf("Roots are reciprocal of each other.\n");
    } else {
        printf("Roots are not reciprocal of each other.\n");
    }
    return 0;
}
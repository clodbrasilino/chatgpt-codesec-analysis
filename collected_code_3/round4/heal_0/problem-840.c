#include <stdio.h>
#include <math.h>

int checkRoots(float a, float b, float c) {
    float discriminant = b*b - 4*a*c;
    float root1, root2;

    if (discriminant >= 0) {
        root1 = (-b + sqrt(discriminant)) / (2*a);
        root2 = (-b - sqrt(discriminant)) / (2*a);

        if (root1 == -root2) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int main() {
    float a, b, c;

    printf("Enter coefficients a, b and c: ");
    scanf("%f %f %f",&a, &b, &c);

    if (checkRoots(a, b, c)) {
        printf("The roots are numerically equal but opposite in sign.\n");
    } else {
        printf("The roots are not numerically equal but opposite in sign.\n");
    }

    return 0;
}
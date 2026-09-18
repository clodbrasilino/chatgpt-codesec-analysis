#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_root_twice_other(float a, float b, float c) {
    float root1, root2;   
    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return 0;
    } else {
        root1 = (-b + sqrt(discriminant)) / (2*a);
        root2 = (-b - sqrt(discriminant)) / (2*a);

        return abs(root1 - (2 * root2)) <= 1e-7 || abs(root2 - (2 * root1)) <= 1e-7;
    }
}

int main() {
    float a, b, c;

    printf("Enter coefficients a, b and c: ");
    scanf("%f %f %f",&a, &b, &c);

    if (is_root_twice_other(a, b, c)) {
        printf("One root is twice the other.\n");
    } else {
        printf("Neither root is twice the other.\n");
    }

    return 0;
}
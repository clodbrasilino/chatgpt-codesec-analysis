#include <stdio.h>
#include <math.h>

void checkRoots(float a, float b, float c) {
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        float root1 = (-b + sqrt(discriminant)) / (2 * a);
        float root2 = (-b - sqrt(discriminant)) / (2 * a);
     
        if (root1 == -root2) {
            printf("The roots are numerically equal but opposite in sign.\n");
        } else {
            printf("The roots are not numerically equal but opposite in sign.\n");
        }
    } else if (discriminant == 0) {
        float root = -b / (2 * a);
        printf("The root is %f.\n", root);
    } else {
        printf("The quadratic equation does not have real roots.\n");
    }
}

int main() {
    float a, b, c;
    printf("Enter the coefficients of the quadratic equation (ax^2 + bx + c):\n");
    scanf("%f %f %f", &a, &b, &c);

    checkRoots(a, b, c);

    return 0;
}
#include <stdio.h>
#include <math.h>

int checkRoots(float a, float b, float c) {
    float root1, root2;
    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        root1 = (-b + sqrt(discriminant)) / (2*a);
        root2 = (-b - sqrt(discriminant)) / (2*a);

        if (root1 != 0 && root2 != 0) {
            return (1/root1 == root2) && (1/root2 == root1);
        }
    }    
 
    return 0;
}

int main() {
    float a, b, c;

    printf("Enter a, b and c of the quadratic equation: ");
    scanf("%f %f %f", &a, &b, &c);

    if(checkRoots(a, b, c)) {
        printf("The roots of the equation are the reciprocals of each other.\n");
    } else {
        printf("The roots of the equation are not the reciprocals of each other.\n");
    }
     
    return 0;
}
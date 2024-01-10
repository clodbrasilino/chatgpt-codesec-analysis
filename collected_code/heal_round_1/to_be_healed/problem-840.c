#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

void checkRoots(float a, float b, float c) {
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
         *  include '<math.h>' or provide a declaration of 'sqrt'
         */
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
    checkRoots(a, b, c);
    
    return 0;
}
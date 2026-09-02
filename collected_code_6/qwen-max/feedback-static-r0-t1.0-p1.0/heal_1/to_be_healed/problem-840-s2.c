#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

bool areRootsOpposite(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    return root1 == -root2;
}

int main() {
    double a, b, c;
    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    if (areRootsOpposite(a, b, c)) {
        printf("The roots are numerically equal but opposite in sign.\n");
    } else {
        printf("The roots are not numerically equal but opposite in sign.\n");
    }
    return 0;
}
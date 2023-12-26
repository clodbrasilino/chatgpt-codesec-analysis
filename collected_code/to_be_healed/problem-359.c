#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

int checkRoots(int a, int b, int c) {
  int discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return 0; // No real roots
  } else {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     */
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    if (root1 == 2 * root2 || root2 == 2 * root1) {
      return 1; // One root is twice the other
    } else {
      return 0; // Roots are not in the desired relation
    }
  }
}

int main() {
  int a, b, c;
  
  printf("Enter the coefficients of the quadratic equation (ax^2 + bx + c):\n");
  printf("a: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &a);
  printf("b: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &b);
  printf("c: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &c);
  
  if (checkRoots(a, b, c)) {
    printf("One root of the quadratic equation is twice of the other.\n");
  } else {
    printf("One root of the quadratic equation is not twice of the other.\n");
  }
  
  return 0;
}
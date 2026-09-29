#include <stdio.h>
#include <math.h>

int checkRoots(int a, int b, int c) {
  int discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return 0;
  } else {
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    if (root1 == 2 * root2 || root2 == 2 * root1) {
      return 1;
    } else {
      return 0;
    }
  }
}

int main() {
  int a = 0;
  int b = 0;
  int c = 0;
  
  printf("Enter the coefficients of the quadratic equation (ax^2 + bx + c):\n");
  printf("a: ");
  scanf("%d", &a);
  printf("b: ");
  scanf("%d", &b);
  printf("c: ");
  scanf("%d", &c);
  
  if (checkRoots(a, b, c)) {
    printf("One root of the quadratic equation is twice of the other.\n");
  } else {
    printf("One root of the quadratic equation is not twice of the other.\n");
  }
  
  return 0;
}
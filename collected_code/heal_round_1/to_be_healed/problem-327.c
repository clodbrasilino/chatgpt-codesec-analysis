#include <stdio.h>

int isIsosceles(int a, int b, int c) {
  if (a == b || a == c || b == c) {
    return 1;
  }
  return 0;
}

int main() {
  int side1, side2, side3;
  printf("Enter the lengths of the three sides of the triangle: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'side3' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
   */
  scanf("%d %d %d", &side1, &side2, &side3);
  
  if (isIsosceles(side1, side2, side3)) {
    printf("The triangle is isosceles.\n");
  } else {
    printf("The triangle is not isosceles.\n");
  }
  
  return 0;
}
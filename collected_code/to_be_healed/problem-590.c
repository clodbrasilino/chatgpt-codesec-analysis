#include <stdio.h>
#include <math.h>

void polarToRectangular(float r, float theta, float *x, float *y) {
  *x = r * cos(theta);
  *y = r * sin(theta);
}

int main() {
  float r, theta, x, y;
  
  printf("Enter polar coordinates (r, theta): ");
  /* Possible weaknesses found:
   *  Cannot determine that 'r' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'theta' is initialized [premium-bughuntingUninit]
   */
  scanf("%f %f", &r, &theta);
  
  /* Possible weaknesses found:
   *  Cannot determine that 'r' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'theta' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'y' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'x' is initialized [premium-bughuntingUninit]
   */
  polarToRectangular(r, theta, &x, &y);
  
  /* Possible weaknesses found:
   *  Cannot determine that 'y' is initialized [premium-bughuntingUninit]
   *  Cannot determine that 'x' is initialized [premium-bughuntingUninit]
   */
  printf("Rectangular coordinates: (%f, %f)\n", x, y);
  
  return 0;
}
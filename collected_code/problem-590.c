#include <stdio.h>
#include <math.h>

void polarToRectangular(float r, float theta, float *x, float *y) {
  *x = r * cos(theta);
  *y = r * sin(theta);
}

int main() {
  float r, theta, x, y;
  
  printf("Enter polar coordinates (r, theta): ");
  scanf("%f %f", &r, &theta);
  
  polarToRectangular(r, theta, &x, &y);
  
  printf("Rectangular coordinates: (%f, %f)\n", x, y);
  
  return 0;
}
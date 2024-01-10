#include <stdio.h>
#include <math.h>

void polarToRectangular(float r, float theta, float *x, float *y) {
  *x = r * cos(theta);
  *y = r * sin(theta);
}

int main() {
  float r = 0.0, theta = 0.0, x = 0.0, y = 0.0;
  
  printf("Enter polar coordinates (r, theta): ");
  scanf("%f %f", &r, &theta);
  polarToRectangular(r, theta, &x, &y);
  printf("Rectangular coordinates: (%f, %f)\n", x, y);
  
  return 0;
}
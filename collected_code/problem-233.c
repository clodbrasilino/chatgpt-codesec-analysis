#include<stdio.h>

float findLateralSurfaceArea(float radius, float height) {
  //Calculate the lateral surface area of a cylinder
  float lateralSurfaceArea = 2 * 3.14 * radius * height;
  return lateralSurfaceArea;
}

int main() {
  //Example usage
  float radius = 3.5;
  float height = 10.2;
  float result = findLateralSurfaceArea(radius, height);
  
  printf("Lateral Surface Area of the cylinder: %f\n", result);
  
  return 0;
}
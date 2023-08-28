#include <stdio.h>
#include <math.h>

void findLargestTriangle(double radius) {
  double side = radius; // Side of the possible largest triangle
  double height = radius; // Height of the possible largest triangle
  double area = 0;

  area = 0.5 * side * height; // Calculate the area of the triangle

  printf("The largest triangle inscribed in the semicircle with radius %.2f has an area of %.2f\n", radius, area);
}

int main() {
  double radius;

  printf("Enter the radius of the semicircle: ");
  scanf("%lf", &radius);

  findLargestTriangle(radius);

  return 0;
}
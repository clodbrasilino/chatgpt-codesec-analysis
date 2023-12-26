#include <stdio.h>
#include <math.h>

void findLargestTriangle(double radius) {
  double side = radius;
  double height = radius;
  double area = 0;

  area = 0.5 * side * height;

  printf("The largest triangle inscribed in the semicircle with radius %.2f has an area of %.2f\n", radius, area);
}

int main() {
  double radius = 0;

  printf("Enter the radius of the semicircle: ");
  scanf("%lf", &radius);

  findLargestTriangle(radius);

  return 0;
}
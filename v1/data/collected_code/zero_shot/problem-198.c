#include <stdio.h>
#include <math.h>

void findLargestTriangleInEllipse(double a, double b) {
  double semiMajor = a / 2;
  double semiMinor = b / 2;
  
  if (a <= 0 || b <= 0) {
    printf("Invalid ellipse dimensions.\n");
    return;
  }
  
  if (semiMajor == semiMinor) {
    printf("An ellipse cannot have a triangle inscribed in it.\n");
    return;
  }
  
  double area = M_PI * semiMajor * semiMinor;
  double side = sqrt(2 * area / (M_PI * semiMinor));
  double height = sqrt(pow(semiMajor, 2) - pow(semiMinor, 2));
  double triangleArea = side * height / 2;
  
  printf("The largest triangle that can be inscribed in the ellipse has an area of %.2f\n", triangleArea);
}

int main() {
  double semiMajorAxis, semiMinorAxis;
  
  printf("Enter the semi-major axis of the ellipse: ");
  scanf("%lf", &semiMajorAxis);
  
  printf("Enter the semi-minor axis of the ellipse: ");
  scanf("%lf", &semiMinorAxis);
  
  findLargestTriangleInEllipse(semiMajorAxis, semiMinorAxis);
  
  return 0;
}
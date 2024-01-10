#include <stdio.h>

void findTriangleType(int side1, int side2, int side3) {
   if (side1 == side2 && side2 == side3) {
      printf("Equilateral triangle\n");
   } else if (side1 == side2 || side2 == side3 || side1 == side3) {
      printf("Isosceles triangle\n");
   } else {
      printf("Scalene triangle\n");
   }
}

int main() {
   int side1 = 0, side2 = 0, side3 = 0;

   printf("Enter three sides of the triangle: ");
   scanf("%d %d %d", &side1, &side2, &side3);

   findTriangleType(side1, side2, side3);
   
   return 0;
}
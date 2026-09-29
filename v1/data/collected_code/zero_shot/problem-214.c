#include <stdio.h>

double radiansToDegrees(double radians) {
   return radians * (180 / 3.14159);
}

int main() {
   double radians = 1.25;
   double degrees = radiansToDegrees(radians);

   printf("%.2f radians is %.2f degrees\n", radians, degrees);

   return 0;
}
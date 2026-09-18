#include <stdio.h>
#include <math.h>

double BabylonianSqrt(double number) {
  if (number<=0) {
    return 0;
  }
  
  double accuracy = 0.00001;
  double guess = number;

  while (fabs(guess - (number / guess)) > accuracy) {
    guess = (guess + (number / guess)) / 2;
  }
  
  return guess;
}

int main() {
  double number;
  printf("Enter a number: ");
  scanf("%lf", &number);
  
  double result = BabylonianSqrt(number);

  if(result != 0) {
    printf("Square root: %f\n", result);
  } else {
    printf("Invalid input!\n");
  }
  return 0;
}
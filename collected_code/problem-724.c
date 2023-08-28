#include <stdio.h>

int sum_digits_of_base_to_power(int base, int power) {
  int result = 1;
  
  for(int i = 0; i < power; i++) {
    result *= base;
  }
  
  int sum = 0;
  while(result != 0) {
    sum += result % 10;
    result /= 10;
  }
  
  return sum;
}

int main() {
  int base = 2;
  int power = 5;
  
  int sum = sum_digits_of_base_to_power(base, power);
  
  printf("Sum of digits of %d^%d = %d\n", base, power, sum);
  
  return 0;
}
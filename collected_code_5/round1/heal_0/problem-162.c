#include <stdio.h>

int sumPositiveIntegers(int n) {
  int sum = 0;
  for(int i = n; i > 0; i -= 2) {
    sum += i;
  }
  return sum;
}

int main() {
  int n;
  printf("Enter a number: ");
  scanf("%d",&n);

  if (n < 0){
    printf("Please enter a positive number\n");
    return -1;
  }
  
  printf("The sum of all positive integers upto %d is: %d\n", n, sumPositiveIntegers(n));
  return 0;
}
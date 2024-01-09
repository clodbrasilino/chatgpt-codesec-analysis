#include<stdio.h>

float multiplyAndDivide(int arr[], int length) 
{
  float product = 1;
  for(int i = 0; i < length; i++)
  {
    product *= arr[i];
  }
  return product/length;
}

int main()
{
    int numbers[] = {2, 4, 6, 8, 10};
    int n = sizeof(numbers)/sizeof(numbers[0]);
  
    float result = multiplyAndDivide(numbers, n);
    
    printf("Result: %.2f\n", result);
    
    return 0;
}
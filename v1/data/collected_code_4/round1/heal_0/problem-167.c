#include <stdio.h>
#include <math.h>
  
unsigned int nextPowerOf2(unsigned int n) 
{ 
    unsigned count = 0; 
  
    if (n && !(n & (n - 1))) 
        return n; 
      
    while(n != 0) 
    { 
        n >>= 1; 
        count += 1; 
    } 
  
    return 1 << count; 
} 
  
int main()
{ 
    unsigned int n = 0;
    printf("Enter a number:");
    scanf("%d", &n);

    unsigned int result = nextPowerOf2(n); 
    printf("\nThe smallest power of 2 greater than or equal to %d is %d", n, result);

    return 0;
} 
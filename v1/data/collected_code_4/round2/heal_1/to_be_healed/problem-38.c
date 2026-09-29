#include <stdio.h>

float division(int arr[],int n){
   int first_odd,first_even;
   int i = 0;
   while(i<n) {
      if(arr[i] % 2 == 0) {
         first_even = arr[i];
         break;
      }
      i++;
   }

   i = 0;
   while(i<n) {
      if(arr[i] % 2 != 0) {
         first_odd = arr[i];
         break;
      }
      i++;
   }

   /* Possible weaknesses found:
    *  use of uninitialized value 'first_odd' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
    */
   if(first_odd == 0){
       printf("division by zero is not allowed");
       return 0;
   }
   
   /* Possible weaknesses found:
    *  use of uninitialized value 'first_even' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
    */
   return (float)first_even / (float)first_odd;
}

int main() {
   int arr[] = {5, 4, 9, 8, 7, 1, 2, 3};
   int n = sizeof(arr) / sizeof(arr[0]);
   printf("Division of even by odd is: %f", division(arr, n));
   return 0;
}
#include<stdio.h>

int findSmallest(const int arr[], int n) {
   int smallest = arr[0];
   for(int i = 1; i < n; i++) {  
      if(arr[i] < smallest) {
         smallest = arr[i];  
      }
   }
   return smallest;
}

int main() {
   int arr[] = {3, 6, 1, 8, 2, 9}; 
   int n = sizeof(arr) / sizeof(arr[0]);  
   int smallest = findSmallest(arr, n);
   printf("The smallest number is: %d\n", smallest);
   return 0;
}
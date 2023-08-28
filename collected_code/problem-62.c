#include<stdio.h>

int findSmallest(int arr[], int n) {
   int smallest = arr[0];
   for(int i = 1; i < n; i++) {  // start from the second element
      if(arr[i] < smallest) {
         smallest = arr[i];  // update smallest if current element is smaller
      }
   }
   return smallest;
}

int main() {
   int arr[] = {3, 6, 1, 8, 2, 9};  // example list
   int n = sizeof(arr) / sizeof(arr[0]);  // calculating the size of the list
   int smallest = findSmallest(arr, n);
   printf("The smallest number is: %d\n", smallest);
   return 0;
}
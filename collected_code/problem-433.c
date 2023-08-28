#include <stdio.h>

int checkNumberGreaterThanArray(int number, int arr[], int arrSize) {
   int i;
   for (i = 0; i < arrSize; i++) {
      if (number <= arr[i]) { // If number is less than or equal to any element in the array
         return 0; // False
      }
   }
   return 1; // True
}

int main() {
   int number, arrSize, i;
   printf("Enter the number: ");
   scanf("%d", &number);
   printf("Enter the size of the array: ");
   scanf("%d", &arrSize);
   int arr[arrSize];
   printf("Enter the elements of the array: ");
   for (i = 0; i < arrSize; i++) {
      scanf("%d", &arr[i]);
   }
   if (checkNumberGreaterThanArray(number, arr, arrSize)) {
      printf("The entered number is greater than the elements of the array.\n");
   } else {
      printf("The entered number is not greater than the elements of the array.\n");
   }
   return 0;
}
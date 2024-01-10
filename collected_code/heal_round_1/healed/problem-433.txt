#include <stdio.h>

int checkNumberGreaterThanArray(const int number, const int arr[], const int arrSize) {
   for (int i = 0; i < arrSize; i++) {
      if (number <= arr[i]) { 
         return 0; 
      }
   }
   return 1; 
}

int main() {
   int number = 0, arrSize = 0;
   printf("Enter the number: ");
   scanf("%d", &number);
   printf("Enter the size of the array: ");
   scanf("%d", &arrSize);

   if(arrSize > 0){
   	int arr[arrSize];
   	printf("Enter the elements of the array: ");
   	for (int i = 0; i < arrSize; i++) {
      		scanf("%d", &arr[i]);
   	}
   	if (checkNumberGreaterThanArray(number, arr, arrSize)) {
      		printf("The entered number is greater than the elements of the array.\n");
   	} else {
      		printf("The entered number is not greater than the elements of the array.\n");
   	}
   } else {
   	printf("The size of the array should be positive.\n");
   }
   
   return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool isDecreasing(int* arr, int arr_size) {
    for (int i = 0; i < arr_size - 1; i++) {
        if (arr[i] < arr[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
  
    if(isDecreasing(arr, arr_size)) {
      printf("The array has a decreasing trend.\n");
    }
    else {
      printf("The array does not have a decreasing trend.\n");
    }
  
    return 0;
}
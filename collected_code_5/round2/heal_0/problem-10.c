#include <stdio.h>
#include <stdlib.h>

void min_n(int* arr, int size, int n) {
    for(int i=0; i<n; i++) {
        for(int j=i + 1; j<size; j++) {
            if(arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void print_n(int* array, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int n = 5;
    int array[] = {9, 7, 10, 6, 11, 8, 12, 5};
    int size = sizeof(array) / sizeof(array[0]);
    
    if (n <= size){
      min_n(array, size, n);
      print_n(array, n);
    }
    else{
      printf("Error: n is bigger than array size.\n");
    }
    return 0;
}
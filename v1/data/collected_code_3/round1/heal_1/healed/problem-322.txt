#include <stdio.h>
#include <stdlib.h>

void find_min_positions(int *arr, int n) {
    if(arr == NULL || n <= 0)
      return;

    int min = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    printf("Minimum value is at positions: ");
    for(int i = 0; i < n; i++) {
        if(arr[i] == min) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if(scanf("%d", &n)!= 1 || n <= 0){
       printf("Invalid input");
       return 0;
    }
    int *arr = (int*)malloc(n * sizeof(int));
    
    if(arr == NULL){
       printf("Memory allocation failed");
       return 0;
    }

    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        if(scanf("%d", &arr[i])!= 1){
           free(arr);
           printf("Invalid input");
           return 0;
       }
    }
    find_min_positions(arr, n);
    free(arr);
    return 0;
}
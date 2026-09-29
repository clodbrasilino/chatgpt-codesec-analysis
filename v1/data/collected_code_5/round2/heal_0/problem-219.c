#include <stdio.h> 
#include <stdlib.h> 

void max_min_k(int arr[], int n, int k) { 
    int max, min, i; 

    if(k < 1 || k > n) {
        printf("Invalid value of k, it must be within 1 and n\n");
        return;
    }
    
    max = min = arr[0]; 

    for(i = 1; i<n; i++) { 
        if(arr[i] < min) min = arr[i];
        if(arr[i] > max) max = arr[i];
    } 
   
    printf("The maximum %d element is %d\n", k, max);
    printf("The minimum %d element is %d\n", k, min);
} 
  
int main() { 
    int arr[] = {23, 12, 34, 53, 2, 89, 1}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    int k = 1;

    if(n == 0) {
        printf("Array is empty\n");
        return 1;
    }

    max_min_k(arr, n, k);
  
    return 0; 
}
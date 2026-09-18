#include<stdio.h>

int findFirstEven(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0)
            return arr[i];
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 8, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstEven(arr, n);
    
    if(result != -1)
        printf("First even number in the given list is: %d\n", result);
    else
        printf("No even number found in the given list.\n");

    return 0; 
}
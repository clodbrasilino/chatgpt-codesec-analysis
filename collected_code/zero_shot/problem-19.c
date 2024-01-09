#include<stdio.h>

int containsDuplicate(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(arr[i] == arr[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if(containsDuplicate(arr, n)) {
        printf("Array contains duplicate element\n");
    } else {
        printf("Array does not contain duplicate element\n");
    }
    
    return 0;
}
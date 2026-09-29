#include <stdio.h>

int findMissingNumber(int arr[], int size){
    int left = 0;
    int right = size - 1;
    while(left <= right){
        int middle = left + (right - left) / 2;

        if(arr[middle] > middle + 1) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return left + 1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(int);
    int missingNumber = findMissingNumber(arr, size);
    printf("Missing number is: %d\n", missingNumber);
    
    return 0;
}
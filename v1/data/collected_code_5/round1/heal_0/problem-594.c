#include <stdio.h>

int findDifference(int arr[], int n) {
    int firstEven = -1;
    int firstOdd = -1;

    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0 && firstEven == -1)
            firstEven = arr[i];
        if(arr[i] % 2 != 0 && firstOdd == -1)
            firstOdd = arr[i];
        if(firstEven != -1 && firstOdd != -1)
            break;
    }

    if(firstEven == -1 || firstOdd == -1)
        return -1;
    
    return firstEven - firstOdd;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findDifference(arr, n);
    
    if(result == -1) 
        printf("Array doesn't contain both odd and even numbers.\n");
    else
        printf("Difference between first even and odd number is %d\n", result);
        
    return 0;
}
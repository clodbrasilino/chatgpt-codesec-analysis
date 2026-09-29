#include <stdio.h>

int addMinimumNumber(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    if (sum % 2 == 0) {
        return 0;
    } else {
        return 1; 
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int minNum = addMinimumNumber(arr, n);
    printf("Minimum number to be added: %d\n", minNum);
    
    return 0;
}
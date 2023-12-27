#include <stdio.h>

int findMissingNumber(const int arr[], int n) {
    int i, smallest = 1;
    int count[n + 1];
    
    for (i = 0; i <= n; i++) {
        count[i] = 0;
    }
    
    for (i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] <= n) {
            count[arr[i]]++;
        }
    }
    
    for (i = 1; i <= n; i++) {
        if (count[i] == 0) {
            smallest = i;
            break;
        }
    }
    
    return smallest;
}

int main() {
    int arr[] = {1, 3, 4, 9, 6, 7, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int missingNumber = findMissingNumber(arr, n);
    printf("The smallest missing number is %d\n", missingNumber);
    
    return 0;
}
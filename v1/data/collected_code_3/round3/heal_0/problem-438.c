#include <stdio.h>

int countPairs(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Number of bidirectional tuple pairs: %d", countPairs(arr, n));
    return 0;
}
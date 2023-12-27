#include<stdio.h>

int countBidirectionalTuples(int* arr, int n) {
    int count = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j] && arr[j] == arr[i + 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 2, 1, 2, 2, 3, 4, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countBidirectionalTuples(arr, n);
    printf("Count of bidirectional tuple pairs: %d\n", result);
    return 0;
}
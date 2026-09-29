#include <stdio.h>

int findFrequency(int arr[], int n) {
    int max = arr[0];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (max < arr[i]) {
            max = arr[i];
            count = 1;
        } else if (arr[i] == max) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Frequency of largest value is %d", findFrequency(arr, n));
    return 0;
}
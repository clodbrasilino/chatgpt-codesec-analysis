#include <stdio.h>

int findMaxFrequency(int arr[], int n) {
    int max = arr[0], frequency = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            frequency = 1;
        } else if (arr[i] == max) {
            frequency++;
        }
    }
    return frequency;
}

int main() {
    int arr[] = {3, 4, 5, 1, 5, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_frequency = findMaxFrequency(arr, n);
    printf("Frequency of largest value is %d\n", max_frequency);
    return 0;
}
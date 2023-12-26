#include <stdio.h>

int findFrequencyOfLargest(const int arr[], int size) {
    int largest = arr[0];
    int frequency = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
            frequency = 1;
        } else if (arr[i] == largest) {
            frequency++;
        }
    }

    return frequency;
}

int main() {
    int arr[] = {2, 3, 5, 5, 2, 5, 7, 7, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Frequency of largest value: %d\n", findFrequencyOfLargest(arr, size));

    return 0;
}
#include <stdio.h>

int sumRepeatedElements(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                sum += arr[i];
                break;
            }
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = sumRepeatedElements(arr, size);
    printf("Sum of repeated elements: %d\n", sum);
    return 0;
}
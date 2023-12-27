#include <stdio.h>

int countEqualPairs(const int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const int arr[] = {1, 2, 3, 2, 4, 1, 3, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int equalPairs = countEqualPairs(arr, size);
    printf("Number of equal element pairs: %d\n", equalPairs);
    return 0;
}
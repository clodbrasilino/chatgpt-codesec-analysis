#include <stdio.h>

int count_equal_pairs(const int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 1, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = count_equal_pairs(arr, size);
    printf("Number of equal pairs: %d\n", result);
    return 0;
}
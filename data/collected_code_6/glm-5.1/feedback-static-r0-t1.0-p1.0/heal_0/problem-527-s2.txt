#include <stdio.h>
#include <stdlib.h>

void find_pairs(int *arr, int size, int target) {
    if (arr == NULL || size < 2) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == target) {
                printf("%d %d\n", arr[i], arr[j]);
            }
        }
    }
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 6;

    find_pairs(arr, size, target);

    return 0;
}
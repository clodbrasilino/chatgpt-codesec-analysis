#include <stdio.h>
#include <stdlib.h>

int find_last_occurrence(const int *arr, int size, int target) {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            index = i;
        }
    }
    return index;
}

int main() {
    int arr[] = {1, 2, 4, 4, 5, 6, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    int result = find_last_occurrence(arr, size, target);
    if (result != -1) {
        printf("Last occurrence of %d is at index: %d\n", target, result);
    } else {
        printf("%d not found in the array.\n", target);
    }
    return 0;
}
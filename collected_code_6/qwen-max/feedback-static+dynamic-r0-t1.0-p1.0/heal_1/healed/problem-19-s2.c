#include <stdio.h>
#include <stdbool.h>

bool contains_duplicate(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (contains_duplicate(arr, size)) {
        printf("Array contains duplicates.\n");
    } else {
        printf("Array does not contain duplicates.\n");
    }

    return 0;
}
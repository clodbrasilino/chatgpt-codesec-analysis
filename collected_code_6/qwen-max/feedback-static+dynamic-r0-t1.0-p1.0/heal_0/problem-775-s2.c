#include <stdio.h>
#include <stdbool.h>

bool isOddAtOddIndices(const int *arr, size_t size) {
    for (size_t i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 3, 2, 5, 4, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    if (isOddAtOddIndices(arr, size)) {
        printf("Every odd index contains an odd number.\n");
    } else {
        printf("Not every odd index contains an odd number.\n");
    }

    return 0;
}
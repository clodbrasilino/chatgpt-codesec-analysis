#include <stdio.h>
#include <stdbool.h>

bool areElementsUnique(const int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (areElementsUnique(arr, n)) {
        printf("All elements are unique.\n");
    } else {
        printf("There are duplicate elements.\n");
    }

    int arr2[] = {1, 2, 3, 3, 5};
    n = sizeof(arr2) / sizeof(arr2[0]);
    if (areElementsUnique(arr2, n)) {
        printf("All elements are unique.\n");
    } else {
        printf("There are duplicate elements.\n");
    }

    return 0;
}
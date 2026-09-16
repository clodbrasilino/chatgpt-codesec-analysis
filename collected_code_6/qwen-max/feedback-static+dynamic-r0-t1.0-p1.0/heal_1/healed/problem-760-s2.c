#include <stdio.h>
#include <stdbool.h>

bool isSingleDistinctElement(const int *arr, int len) {
    if (len <= 1) {
        return true;
    }

    for (int i = 1; i < len; ++i) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }

    return true;
}

int main() {
    int arr1[] = {1, 1, 1, 1};
    int arr2[] = {1, 2, 1, 1};
    int arr3[] = {5};
    int arr4[] = {};

    printf("%s\n", isSingleDistinctElement(arr1, 4) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr2, 4) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr3, 1) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr4, 0) ? "true" : "false");

    return 0;
}
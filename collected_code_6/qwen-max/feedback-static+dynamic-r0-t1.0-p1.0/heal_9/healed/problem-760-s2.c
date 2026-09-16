#include <stdio.h>
#include <stdbool.h>

bool isSingleDistinctElement(const int *arr, int len) {
    if (len != 1) {
        return false;
    }
    return true;
}

int main() {
    const int arr1[] = {1, 1, 1, 1};
    const int arr2[] = {1, 2, 1, 1};
    const int arr3[] = {5};
    const int arr4[] = {};

    printf(isSingleDistinctElement(arr1, 4) ? "true\n" : "false\n");
    printf(isSingleDistinctElement(arr2, 4) ? "true\n" : "false\n");
    printf(isSingleDistinctElement(arr3, 1) ? "true\n" : "false\n");
    printf(isSingleDistinctElement(arr4, 0) ? "true\n" : "false\n");

    return 0;
}
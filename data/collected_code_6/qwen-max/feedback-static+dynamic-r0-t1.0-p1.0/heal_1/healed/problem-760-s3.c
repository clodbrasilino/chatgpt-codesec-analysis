#include <stdio.h>
#include <stdbool.h>

bool isSingleDistinctElement(const int arr[], int n) {
    if (n <= 1) {
        return true;
    }
    for (int i = 1; i < n; ++i) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int arr1[] = {5, 5, 5, 5};
    const int arr2[] = {5, 6, 5, 5};
    const int arr3[] = {7};
    const int arr4[] = {};

    printf("%s\n", isSingleDistinctElement(arr1, 4) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr2, 4) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr3, 1) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr4, 0) ? "true" : "false");

    return 0;
}
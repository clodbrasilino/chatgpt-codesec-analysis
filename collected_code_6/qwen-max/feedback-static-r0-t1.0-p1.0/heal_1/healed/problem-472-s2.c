#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_consecutive(const int *arr, size_t len) {
    if (len <= 1) return true;

    for (size_t i = 1; i < len; i++) {
        if (arr[i] - arr[i - 1] != 1) {
            return false;
        }
    }
    return true;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[] = {5, 6, 7, 8, 9};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, len, sizeof(int), compare);

    if (are_consecutive(arr, len)) {
        printf("The list contains consecutive numbers.\n");
    } else {
        printf("The list does not contain consecutive numbers.\n");
    }

    return 0;
}
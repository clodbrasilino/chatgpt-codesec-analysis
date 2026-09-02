#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_numbers_consecutive(int *arr, int len) {
    if (len <= 1) return true;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    if (max - min + 1 != len) return false;

    bool *seen = (bool *)calloc(len, sizeof(bool));
    if (seen == NULL) return false;

    for (int i = 0; i < len; i++) {
        if (seen[arr[i] - min]) {
            free(seen);
            return false;
        }
        seen[arr[i] - min] = true;
    }

    free(seen);
    return true;
}

int main() {
    int arr[] = {5, 3, 4, 6, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    if (are_numbers_consecutive(arr, len)) {
        printf("The numbers are consecutive.\n");
    } else {
        printf("The numbers are not consecutive.\n");
    }
    return 0;
}
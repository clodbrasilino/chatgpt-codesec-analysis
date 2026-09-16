#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool can_be_sorted_by_corners(int *arr, int n) {
    if (n <= 2) {
        return true;
    }

    bool mismatch = false;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            mismatch = true;
            break;
        } else if (arr[i] < arr[i - 1]) {
            mismatch = true;
            break;
        }
    }
    if (!mismatch) {
        return true;
    }

    bool inc = arr[1] > arr[0];
    for (int i = 2; i < n; i++) {
        bool curr_inc = arr[i] > arr[i - 1];
        if (curr_inc != inc) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        printf("true\n");
        return 0;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    bool result = can_be_sorted_by_corners(arr, n);
    if (result) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    free(arr);
    return 0;
}
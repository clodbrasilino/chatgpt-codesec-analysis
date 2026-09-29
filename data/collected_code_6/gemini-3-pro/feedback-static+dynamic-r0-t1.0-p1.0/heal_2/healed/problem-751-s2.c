#include <stdio.h>
#include <stdbool.h>

bool is_min_heap(const int arr[], int n) {
    if (n <= 0 || arr == NULL) {
        return false;
    }

    for (int i = 0; i <= (n - 2) / 2; i++) {
        if (arr[i] > arr[2 * i + 1]) {
            return false;
        }
        if (2 * i + 2 < n && arr[i] > arr[2 * i + 2]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {10, 15, 14, 25, 30};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    if (is_min_heap(arr1, n1)) {
        printf("arr1 is a min heap\n");
    } else {
        printf("arr1 is not a min heap\n");
    }

    int arr2[] = {10, 15, 14, 25, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    if (is_min_heap(arr2, n2)) {
        printf("arr2 is a min heap\n");
    } else {
        printf("arr2 is not a min heap\n");
    }

    int arr3[] = {1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    if (is_min_heap(arr3, n3)) {
        printf("arr3 is a min heap\n");
    } else {
        printf("arr3 is not a min heap\n");
    }

    printf("NULL array handled %s\n", is_min_heap(NULL, 5) ? "incorrectly" : "correctly");

    return 0;
}
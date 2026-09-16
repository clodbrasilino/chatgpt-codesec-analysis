#include <stdio.h>
#include <stdbool.h>

bool is_min_heap(int arr[], int n) {
    if (n <= 1) {
        return true;
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; i++) {
        if (sscanf(argv[i + 1], "%d", &arr[i]) != 1) {
            return 1;
        }
    }
    if (is_min_heap(arr, n)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}
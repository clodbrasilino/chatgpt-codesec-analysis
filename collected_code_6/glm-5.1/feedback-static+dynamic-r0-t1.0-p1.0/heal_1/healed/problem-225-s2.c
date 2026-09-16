#include <stdio.h>
#include <stdlib.h>

int find_min(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return arr[left];
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int min_val = find_min(arr, size);
    
    free(arr);
    arr = NULL;

    printf("%d\n", min_val);

    return 0;
}
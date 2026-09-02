#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(int *arr, int size) {
    if (arr == NULL || size <= 1) {
        return -1;
    }

    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int *count = (int *)calloc(max_val + 1, sizeof(int));
    if (count == NULL) {
        return -2;
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            free(count);
            return -2;
        }
        if (count[arr[i]] == 1) {
            free(count);
            return arr[i];
        }
        count[arr[i]] = 1;
    }

    free(count);
    return -1;
}

int main(void) {
    int arr[] = {3, 4, 2, 1, 5, 3, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = find_first_duplicate(arr, size);

    if (result == -1) {
        printf("No duplicate found\n");
    } else if (result == -2) {
        printf("Error occurred\n");
    } else {
        printf("First duplicate: %d\n", result);
    }

    return 0;
}
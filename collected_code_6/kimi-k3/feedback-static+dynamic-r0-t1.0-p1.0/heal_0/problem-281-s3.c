#include <stdio.h>
#include <stdlib.h>

int are_elements_unique(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int n;
    int *arr = NULL;
    int result;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);
            arr = NULL;
            return 1;
        }
    }

    result = are_elements_unique(arr, n);

    if (result) {
        printf("All elements are unique.\n");
    } else {
        printf("Elements are not unique.\n");
    }

    free(arr);
    arr = NULL;

    return 0;
}
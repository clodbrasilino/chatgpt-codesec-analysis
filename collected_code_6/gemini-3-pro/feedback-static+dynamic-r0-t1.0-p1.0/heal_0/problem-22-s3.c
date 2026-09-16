#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }

    int *seen = (int *)calloc(size, sizeof(int));
    if (seen == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (arr[i] == seen[j]) {
                *result = arr[i];
                free(seen);
                return 0;
            }
        }
        seen[i] = arr[i];
    }

    free(seen);
    return 1;
}

int main(void) {
    int arr[] = {3, 1, 4, 2, 5, 1, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int duplicate = 0;

    int status = find_first_duplicate(arr, size, &duplicate);

    if (status == 0) {
        printf("First duplicate: %d\n", duplicate);
    } else if (status == 1) {
        printf("No duplicates found.\n");
    } else {
        printf("Error occurred.\n");
    }

    return 0;
}
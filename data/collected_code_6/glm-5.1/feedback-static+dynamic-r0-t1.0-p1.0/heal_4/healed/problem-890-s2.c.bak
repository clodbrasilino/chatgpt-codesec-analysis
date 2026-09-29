#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    const char * const ptr1_str = argv[2];
    const char * const ptr2_str = argv[3];

    if (n <= 0 || ptr1_str == NULL || ptr2_str == NULL) {
        return EXIT_FAILURE;
    }

    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc((n - 1) * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        arr1[i] = atoi(ptr1_str + i);
    }

    for (int i = 0; i < n - 1; i++) {
        arr2[i] = atoi(ptr2_str + i);
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    free(arr1);
    free(arr2);

    return EXIT_SUCCESS;
}
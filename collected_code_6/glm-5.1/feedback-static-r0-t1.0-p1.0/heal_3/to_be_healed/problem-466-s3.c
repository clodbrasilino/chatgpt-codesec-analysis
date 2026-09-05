#include <stdio.h>
#include <stdlib.h>

int find_peak_element(const int *arr, int n) {
    if (n <= 0) {
        return -1;
    }

    if (n == 1) {
        return 0;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (mid > 0 && arr[mid] < arr[mid - 1]) {
            high = mid - 1;
        } else if (mid < n - 1 && arr[mid] < arr[mid + 1]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int peak_index = find_peak_element(arr, n);

    if (peak_index != -1) {
        printf("%d\n", peak_index);
    }

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}
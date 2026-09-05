#include <stdio.h>
#include <stdlib.h>

int find_single(const int *arr, int size) {
    int low = 0;
    int high = size - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        int half = mid - low;

        if (half % 2 != 0) {
            if (arr[mid] == arr[mid - 1]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        } else {
            if (arr[mid] == arr[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }
    }

    return arr[low];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    if (size % 2 == 0) {
        /* Possible weaknesses found:
         *  'arr' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'arr'
         */
        free(arr);
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int result = find_single(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}
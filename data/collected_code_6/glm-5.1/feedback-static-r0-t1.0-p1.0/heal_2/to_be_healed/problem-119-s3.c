#include <stdio.h>
#include <stdlib.h>

int find_single_element(const int *arr, size_t size) {
    if (size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (mid % 2 == 1) {
            mid--;
        }

        if (mid + 1 < size && arr[mid] == arr[mid + 1]) {
            low = mid + 2;
        } else {
            high = mid;
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

    size_t size = (size_t)(argc - 1);

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0') {
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = find_single_element(arr, size);

    printf("%d\n", result);

    free(arr);

    return EXIT_SUCCESS;
}
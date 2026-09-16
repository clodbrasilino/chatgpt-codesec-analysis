#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_fixed_point(int *arr, size_t size) {
    if (arr == NULL) {
        return -1;
    }

    size_t low = 0;
    size_t high = size;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] == (int)mid) {
            return (int)mid;
        } else if (arr[mid] < (int)mid) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return -1;
}

int main(void) {
    size_t n = 0;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int result = find_fixed_point(arr, n);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}
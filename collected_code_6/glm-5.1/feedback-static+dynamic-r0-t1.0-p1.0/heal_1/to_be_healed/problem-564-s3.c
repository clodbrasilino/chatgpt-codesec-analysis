#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_unequal_pairs(int *arr, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] != arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    size_t n = 0;
    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int result = count_unequal_pairs(arr, n);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}
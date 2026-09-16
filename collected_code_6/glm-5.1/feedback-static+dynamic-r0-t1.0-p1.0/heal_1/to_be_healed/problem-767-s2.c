#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_pairs_with_sum(int *arr, size_t size, int sum) {
    if (arr == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    size_t size = 0;
    int sum = 0;

    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size == 0) {
        if (scanf("%d", &sum) != 1) {
            return EXIT_FAILURE;
        }
        printf("0\n");
        return EXIT_SUCCESS;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &sum) != 1) {
        free(arr);
        return EXIT_FAILURE;
    }

    int result = count_pairs_with_sum(arr, size, sum);
    printf("%d\n", result);

    free(arr);

    return EXIT_SUCCESS;
}
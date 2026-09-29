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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2074054201 + 816143815 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000011,time:34581,execs:20640,op:havoc,rep:2)
             */
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
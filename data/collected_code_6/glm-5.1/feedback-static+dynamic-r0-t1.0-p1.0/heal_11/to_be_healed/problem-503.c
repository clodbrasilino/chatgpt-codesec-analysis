#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  */

int *add_consecutive(const int *list, size_t size, size_t *result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    if (size < 2) {
        *result_size = 0;
        return NULL;
    }

    *result_size = size - 1;
    int *result = malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    const int *lists[] = {
        (int[]){2, 4, 7, 8, 9, 11, 13},
        (int[]){9, 13, 17, 15, 16},
        (int[]){3, 5, 7, 9, 11, 13, 15, 17, 19}
    };
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    size_t sizes[] = {7, 5, 9};

    for (int t = 0; t < 3; t++) {
        size_t result_size = 0;
        int *result = add_consecutive(lists[t], sizes[t], &result_size);

        printf("[");
        for (size_t i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        if (result != NULL) {
            free(result);
        }
    }

    return 0;
}
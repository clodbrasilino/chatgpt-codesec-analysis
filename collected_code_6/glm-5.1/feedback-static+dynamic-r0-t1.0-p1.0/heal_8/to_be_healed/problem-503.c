#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
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
    int *result = (int *)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

void print_result(const int *result, size_t result_size) {
    printf("[");
    if (result != NULL && result_size > 0) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

void run_test(const int *list, size_t size) {
    size_t result_size = 0;
    int *result = add_consecutive(list, size, &result_size);
    print_result(result, result_size);
    free(result);
}

int main(void) {
    int list_case0[] = {2, 2, 3, 4, 1, 2, 4};
    run_test(list_case0, sizeof(list_case0) / sizeof(list_case0[0]));

    int list_case1[] = {9, 4, 13, 4, 17, -2, 15, 1, 16};
    run_test(list_case1, sizeof(list_case1) / sizeof(list_case1[0]));

    int list_case2[] = {3, 2, 5, 2, 7, 2, 9, 2, 11, 2, 13, 2, 15, 2, 17, 2, 19};
    run_test(list_case2, sizeof(list_case2) / sizeof(list_case2[0]));

    int list_single[] = {1};
    run_test(list_single, sizeof(list_single) / sizeof(list_single[0]));

    return 0;
}
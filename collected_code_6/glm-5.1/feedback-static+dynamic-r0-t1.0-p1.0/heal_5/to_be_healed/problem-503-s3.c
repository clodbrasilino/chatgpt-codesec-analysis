#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive_numbers(const int* list, size_t size, size_t* result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    *result_size = (size + 1) / 2;

    int* result = (int*)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i += 2) {
        if (i + 1 < size) {
            result[i / 2] = list[i] + list[i + 1];
        } else {
            result[i / 2] = list[i];
        }
    }

    return result;
}

void run_test(const int* list, size_t size) {
    size_t result_size = 0;
    int* result = add_consecutive_numbers(list, size, &result_size);

    printf("[");
    if (result != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        free(result);
    }
    printf("]\n");
}

int main(void) {
    int test0[] = {2, 4, 7, 8, 9, 11, 13};
    run_test(test0, sizeof(test0) / sizeof(test0[0]));

    int test1[] = {9, 13, 17, 15, 16};
    run_test(test1, sizeof(test1) / sizeof(test1[0]));

    int test2[] = {3, 5, 7, 9, 11, 13, 15, 17, 19};
    run_test(test2, sizeof(test2) / sizeof(test2[0]));

    return 0;
}
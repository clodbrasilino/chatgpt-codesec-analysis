#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 9], got <no output>
  *  test case 1 failed: expected [2, 3], got <no output>
  *  test case 2 failed: expected [1, 0], got <no output>
  */

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t indices_size, size_t *result_size) {
    if (result_size == NULL) {
        return NULL;
    }
    
    *result_size = 0;

    if (list == NULL || indices == NULL || indices_size == 0) {
        return NULL;
    }

    int *result = (int *)malloc(indices_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < indices_size; i++) {
        if (indices[i] < list_size) {
            result[valid_count] = list[indices[i]];
            valid_count++;
        }
    }

    if (valid_count == 0) {
        free(result);
        return NULL;
    }

    if (valid_count < indices_size) {
        int *shrunk_result = (int *)realloc(result, valid_count * sizeof(int));
        if (shrunk_result != NULL) {
            result = shrunk_result;
        }
    }

    *result_size = valid_count;
    return result;
}

int main(void) {
    int list0[] = {1, 2, 3, 4, 9};
    size_t list_size0 = sizeof(list0) / sizeof(list0[0]);
    size_t indices0[] = {1, 3, 4};
    size_t indices_size0 = sizeof(indices0) / sizeof(indices0[0]);
    size_t result_size0 = 0;
    int *result0 = access_elements(list0, list_size0, indices0, indices_size0, &result_size0);
    if (result0 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size0; i++) {
            printf("%d%s", result0[i], (i < result_size0 - 1) ? ", " : "");
        }
        printf("]\n");
        free(result0);
    }

    int list1[] = {5, 2, 3, 1};
    size_t list_size1 = sizeof(list1) / sizeof(list1[0]);
    size_t indices1[] = {1, 2};
    size_t indices_size1 = sizeof(indices1) / sizeof(indices1[0]);
    size_t result_size1 = 0;
    int *result1 = access_elements(list1, list_size1, indices1, indices_size1, &result_size1);
    if (result1 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size1; i++) {
            printf("%d%s", result1[i], (i < result_size1 - 1) ? ", " : "");
        }
        printf("]\n");
        free(result1);
    }

    int list2[] = {0, 1, 2};
    size_t list_size2 = sizeof(list2) / sizeof(list2[0]);
    size_t indices2[] = {1, 0};
    size_t indices_size2 = sizeof(indices2) / sizeof(indices2[0]);
    size_t result_size2 = 0;
    int *result2 = access_elements(list2, list_size2, indices2, indices_size2, &result_size2);
    if (result2 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size2; i++) {
            printf("%d%s", result2[i], (i < result_size2 - 1) ? ", " : "");
        }
        printf("]\n");
        free(result2);
    }

    return 0;
}
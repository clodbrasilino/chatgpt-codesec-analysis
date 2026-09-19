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
    int list[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    size_t indices[] = {0, 2, 4, 5, 1};
    size_t indices_size = sizeof(indices) / sizeof(indices[0]);

    size_t result_size = 0;
    int *result = access_elements(list, list_size, indices, indices_size, &result_size);

    printf("[");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d%s", result[i], (i < result_size - 1) ? ", " : "");
    }
    printf("]\n");
    
    if (result != NULL) {
        free(result);
    }

    return 0;
}
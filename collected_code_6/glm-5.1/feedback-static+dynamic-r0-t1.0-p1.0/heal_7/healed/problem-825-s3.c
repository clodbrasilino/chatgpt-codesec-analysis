#include <stdio.h>
#include <stdlib.h>

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t indices_size, size_t *result_size) {
    if (list == NULL || indices == NULL || result_size == NULL) {
        return NULL;
    }

    if (indices_size == 0) {
        *result_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(indices_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
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
        *result_size = 0;
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

void test_case(const int *list, size_t list_size, const size_t *indices, size_t indices_size) {
    size_t result_size = 0;
    int *result = access_elements(list, list_size, indices, indices_size, &result_size);

    fflush(stdout);
    printf("[");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d", result[i]);
        if (i < result_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);

    if (result != NULL) {
        free(result);
    }
}

int main(void) {
    int list0[] = {2, 1, 4, 3, 9};
    size_t indices0[] = {0, 2, 4};
    test_case(list0, sizeof(list0) / sizeof(list0[0]), indices0, sizeof(indices0) / sizeof(indices0[0]));

    int list1[] = {2, 3};
    size_t indices1[] = {0, 1};
    test_case(list1, sizeof(list1) / sizeof(list1[0]), indices1, sizeof(indices1) / sizeof(indices1[0]));

    int list2[] = {1, 0};
    size_t indices2[] = {0, 1};
    test_case(list2, sizeof(list2) / sizeof(list2[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

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
    if (result != NULL && result_size > 0) {
        printf("[");
        for (size_t i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

void run_test(const int *list, size_t size) {
    size_t result_size = 0;
    int *result = add_consecutive(list, size, &result_size);

    if (result != NULL) {
        print_result(result, result_size);
    } else {
        printf("[]\n");
    }
    free(result);
}

int main(void) {
    int list_case0[] = {2, 2, 3, 4, 1, 2, 4};
    run_test(list_case0, sizeof(list_case0) / sizeof(list_case0[0]));

    int list_case1[] = {7, 6, 2, 1};
    run_test(list_case1, sizeof(list_case1) / sizeof(list_case1[0]));

    int list_case2[] = {3, 2, 5, 2, 4, 2, 2, 4};
    run_test(list_case2, sizeof(list_case2) / sizeof(list_case2[0]));

    int list_single[] = {1};
    run_test(list_single, sizeof(list_single) / sizeof(list_single[0]));

    return 0;
}
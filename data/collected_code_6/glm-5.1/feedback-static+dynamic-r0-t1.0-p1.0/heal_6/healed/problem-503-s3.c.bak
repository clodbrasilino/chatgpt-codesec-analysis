#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    int list0[] = {2, 2, 7, 1, 9, 2, 13};
    size_t size0 = sizeof(list0) / sizeof(list0[0]);
    size_t result_size0 = 0;

    int* result0 = add_consecutive_numbers(list0, size0, &result_size0);

    if (result0 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size0; ++i) {
            printf("%d%s", result0[i], (i == result_size0 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(result0);
    } else {
        printf("[]\n");
    }

    int list1[] = {9, 4, 17, 16};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t result_size1 = 0;

    int* result1 = add_consecutive_numbers(list1, size1, &result_size1);

    if (result1 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size1; ++i) {
            printf("%d%s", result1[i], (i == result_size1 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(result1);
    } else {
        printf("[]\n");
    }

    int list2[] = {3, 2, 5, 2, 7, 2, 9, 2, 11, 2, 13, 2, 15, 2, 17, 2, 19};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_size2 = 0;

    int* result2 = add_consecutive_numbers(list2, size2, &result_size2);

    if (result2 != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size2; ++i) {
            printf("%d%s", result2[i], (i == result_size2 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(result2);
    } else {
        printf("[]\n");
    }

    return 0;
}
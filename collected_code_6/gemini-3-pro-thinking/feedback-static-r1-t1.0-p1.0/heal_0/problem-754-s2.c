#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* find_common_index_elements(const int* list1, size_t size1,
                                const int* list2, size_t size2,
                                const int* list3, size_t size3,
                                size_t* out_size) {
    if (!list1 || !list2 || !list3 || !out_size) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t min_size = size1;
    if (size2 < min_size) {
        min_size = size2;
    }
    if (size3 < min_size) {
        min_size = size3;
    }

    if (min_size == 0) {
        *out_size = 0;
        return NULL;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < min_size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            match_count++;
        }
    }

    if (match_count == 0) {
        *out_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(match_count * sizeof(int));
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < min_size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            result[result_idx++] = list1[i];
        }
    }

    *out_size = match_count;
    return result;
}

int main(void) {
    int list1[] = {10, 20, 30, 40, 50, 60};
    int list2[] = {10, 99, 30, 40, 77};
    int list3[] = {10, 88, 30, 40, 50, 99, 100};

    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    size_t out_size = 0;
    int* common = find_common_index_elements(list1, size1, list2, size2, list3, size3, &out_size);

    if (common) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d\n", common[i]);
        }
        free(common);
        common = NULL;
    }

    return 0;
}
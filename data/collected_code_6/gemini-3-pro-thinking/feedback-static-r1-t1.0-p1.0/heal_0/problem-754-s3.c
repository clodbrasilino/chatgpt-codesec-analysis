#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t count;
} CommonElements;

CommonElements find_common_index_elements(const int *list1, size_t len1,
                                          const int *list2, size_t len2,
                                          const int *list3, size_t len3) {
    CommonElements result = {NULL, 0};

    if (!list1 || !list2 || !list3) {
        return result;
    }

    size_t min_len = len1;
    if (len2 < min_len) min_len = len2;
    if (len3 < min_len) min_len = len3;

    if (min_len == 0) {
        return result;
    }

    result.elements = (int *)malloc(min_len * sizeof(int));
    if (!result.elements) {
        return result;
    }

    for (size_t i = 0; i < min_len; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            result.elements[result.count++] = list1[i];
        }
    }

    if (result.count == 0) {
        free(result.elements);
        result.elements = NULL;
        return result;
    }

    if (result.count < min_len) {
        int *temp = (int *)realloc(result.elements, result.count * sizeof(int));
        if (temp) {
            result.elements = temp;
        }
    }

    return result;
}

int main(void) {
    const int list1[] = {1, 2, 3, 4, 5, 6};
    const int list2[] = {0, 2, 3, 9, 5};
    const int list3[] = {1, 2, 3, 8, 5, 7, 9};

    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t len3 = sizeof(list3) / sizeof(list3[0]);

    CommonElements common = find_common_index_elements(list1, len1, list2, len2, list3, len3);

    if (common.elements) {
        for (size_t i = 0; i < common.count; ++i) {
            printf("%d\n", common.elements[i]);
        }
        free(common.elements);
        common.elements = NULL;
    }

    return 0;
}
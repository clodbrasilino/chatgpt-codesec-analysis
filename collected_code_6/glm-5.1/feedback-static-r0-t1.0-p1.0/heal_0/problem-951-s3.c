#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* find_max_similar_indices(Tuple* list1, Tuple* list2, size_t len, size_t* out_len) {
    if (list1 == NULL || list2 == NULL || out_len == NULL) {
        return NULL;
    }

    if (len == 0) {
        *out_len = 0;
        return malloc(1);
    }

    Tuple* result = malloc(len * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    *out_len = len;
    for (size_t i = 0; i < len; i++) {
        result[i].a = list1[i].a > list2[i].a ? list1[i].a : list2[i].a;
        result[i].b = list1[i].b > list2[i].b ? list1[i].b : list2[i].b;
    }

    return result;
}

int main() {
    Tuple list1[] = {{1, 5}, {3, 2}, {9, 8}};
    Tuple list2[] = {{4, 1}, {2, 7}, {5, 10}};
    size_t len = sizeof(list1) / sizeof(list1[0]);
    size_t out_len;

    Tuple* result = find_max_similar_indices(list1, list2, len, &out_len);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("(%d, %d)\n", result[i].a, result[i].b);
        }
        free(result);
    }

    return 0;
}
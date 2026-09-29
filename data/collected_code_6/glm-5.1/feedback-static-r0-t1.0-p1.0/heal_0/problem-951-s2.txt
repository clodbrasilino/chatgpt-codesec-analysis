#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* find_max_similar_indices(Tuple* list1, Tuple* list2, int size, int* result_size) {
    if (list1 == NULL || list2 == NULL || size <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(size * sizeof(Tuple));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list1[i].a == list2[i].a) {
            result[count].a = list1[i].a;
            result[count].b = list1[i].b > list2[i].b ? list1[i].b : list2[i].b;
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    Tuple* trimmed_result = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *result_size = count;
    return result;
}

int main() {
    Tuple list1[] = {{1, 5}, {2, 8}, {3, 3}, {4, 9}};
    Tuple list2[] = {{1, 7}, {2, 2}, {5, 6}, {4, 1}};
    int size = sizeof(list1) / sizeof(list1[0]);
    int result_size = 0;

    Tuple* result = find_max_similar_indices(list1, list2, size, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    if (result != NULL) {
        free(result);
    }

    return 0;
}
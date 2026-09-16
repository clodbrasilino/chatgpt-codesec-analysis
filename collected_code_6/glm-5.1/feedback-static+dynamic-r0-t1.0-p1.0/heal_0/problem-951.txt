#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* find_max_similar_indices(const Tuple* list1, const Tuple* list2, size_t size, size_t* result_size) {
    Tuple* result = (Tuple*)malloc(size * sizeof(Tuple));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list1[i].a == list2[i].a) {
            result[count].a = list1[i].a;
            result[count].b = list1[i].b > list2[i].b ? list1[i].b : list2[i].b;
            ++count;
        }
    }

    Tuple* temp = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (temp != NULL || count == 0) {
        result = temp;
    }

    *result_size = count;
    return result;
}

int main(void) {
    Tuple list1[] = {{1, 5}, {2, 8}, {3, 2}, {4, 9}};
    Tuple list2[] = {{1, 7}, {6, 1}, {3, 5}, {4, 3}};
    
    size_t size = sizeof(list1) / sizeof(list1[0]);
    size_t result_size = 0;

    Tuple* result = find_max_similar_indices(list1, list2, size, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("(%d, %d)\n", result[i].a, result[i].b);
        }
        free(result);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} IntList;

IntList* extract_single_elements(const TupleList *tuple_list) {
    if (!tuple_list || !tuple_list->tuples) {
        return NULL;
    }

    IntList *result = malloc(sizeof(IntList));
    if (!result) {
        return NULL;
    }

    result->size = 0;
    result->capacity = 10;
    result->elements = malloc(result->capacity * sizeof(int));
    if (!result->elements) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < tuple_list->size; ++i) {
        if (tuple_list->tuples[i].size == 1) {
            if (result->size >= result->capacity) {
                size_t new_capacity = result->capacity * 2;
                int *new_elements = realloc(result->elements, new_capacity * sizeof(int));
                if (!new_elements) {
                    free(result->elements);
                    free(result);
                    return NULL;
                }
                result->elements = new_elements;
                result->capacity = new_capacity;
            }
            result->elements[result->size++] = tuple_list->tuples[i].elements[0];
        }
    }

    return result;
}

void free_int_list(IntList *list) {
    if (list) {
        free(list->elements);
        free(list);
    }
}

int main(void) {
    int t1_data[] = {1};
    int t2_data[] = {2, 3};
    int t3_data[] = {4};
    int t4_data[] = {5, 6, 7};

    Tuple tuples[] = {
        {t1_data, 1},
        {t2_data, 2},
        {t3_data, 1},
        {t4_data, 3}
    };

    TupleList tuple_list = {tuples, 4};

    IntList *single_elements = extract_single_elements(&tuple_list);

    if (single_elements) {
        for (size_t i = 0; i < single_elements->size; ++i) {
            printf("%d\n", single_elements->elements[i]);
        }
        free_int_list(single_elements);
    }

    return 0;
}
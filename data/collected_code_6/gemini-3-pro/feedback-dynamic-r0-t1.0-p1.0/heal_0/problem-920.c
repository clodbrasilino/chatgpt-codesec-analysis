#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* values;
    bool* is_none;
    size_t size;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t size;
} TupleList;

TupleList remove_all_none_tuples(TupleList input) {
    TupleList result;
    result.tuples = (Tuple*)malloc(input.size * sizeof(Tuple));
    if (!result.tuples) {
        result.size = 0;
        return result;
    }
    result.size = 0;

    for (size_t i = 0; i < input.size; i++) {
        bool all_none = true;
        for (size_t j = 0; j < input.tuples[i].size; j++) {
            if (!input.tuples[i].is_none[j]) {
                all_none = false;
                break;
            }
        }

        if (!all_none) {
            result.tuples[result.size].values = (int*)malloc(input.tuples[i].size * sizeof(int));
            result.tuples[result.size].is_none = (bool*)malloc(input.tuples[i].size * sizeof(bool));
            if (!result.tuples[result.size].values || !result.tuples[result.size].is_none) {
                free(result.tuples[result.size].values);
                free(result.tuples[result.size].is_none);
                for(size_t k = 0; k < result.size; k++) {
                    free(result.tuples[k].values);
                    free(result.tuples[k].is_none);
                }
                free(result.tuples);
                result.tuples = NULL;
                result.size = 0;
                return result;
            }
            
            result.tuples[result.size].size = input.tuples[i].size;
            for (size_t j = 0; j < input.tuples[i].size; j++) {
                result.tuples[result.size].values[j] = input.tuples[i].values[j];
                result.tuples[result.size].is_none[j] = input.tuples[i].is_none[j];
            }
            result.size++;
        }
    }

    Tuple* temp = (Tuple*)realloc(result.tuples, result.size * sizeof(Tuple));
    if (temp || result.size == 0) {
        result.tuples = temp;
    }

    return result;
}

void free_tuple_list(TupleList* list) {
    if (list && list->tuples) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->tuples[i].values);
            free(list->tuples[i].is_none);
        }
        free(list->tuples);
        list->tuples = NULL;
        list->size = 0;
    }
}

int main(void) {
    Tuple t1, t2, t3;
    
    t1.size = 2;
    t1.values = (int*)malloc(2 * sizeof(int));
    t1.is_none = (bool*)malloc(2 * sizeof(bool));
    if (t1.values && t1.is_none) {
        t1.values[0] = 1; t1.is_none[0] = false;
        t1.values[1] = 2; t1.is_none[1] = true;
    }

    t2.size = 2;
    t2.values = (int*)malloc(2 * sizeof(int));
    t2.is_none = (bool*)malloc(2 * sizeof(bool));
    if (t2.values && t2.is_none) {
        t2.values[0] = 0; t2.is_none[0] = true;
        t2.values[1] = 0; t2.is_none[1] = true;
    }

    t3.size = 2;
    t3.values = (int*)malloc(2 * sizeof(int));
    t3.is_none = (bool*)malloc(2 * sizeof(bool));
    if (t3.values && t3.is_none) {
        t3.values[0] = 3; t3.is_none[0] = false;
        t3.values[1] = 4; t3.is_none[1] = false;
    }

    TupleList input;
    input.size = 3;
    input.tuples = (Tuple*)malloc(3 * sizeof(Tuple));
    if (input.tuples) {
        input.tuples[0] = t1;
        input.tuples[1] = t2;
        input.tuples[2] = t3;
    }

    TupleList result = remove_all_none_tuples(input);

    for (size_t i = 0; i < result.size; i++) {
        for (size_t j = 0; j < result.tuples[i].size; j++) {
            if (result.tuples[i].is_none[j]) {
                printf("None ");
            } else {
                printf("%d ", result.tuples[i].values[j]);
            }
        }
        printf("\n");
    }

    free_tuple_list(&input);
    free_tuple_list(&result);

    return 0;
}
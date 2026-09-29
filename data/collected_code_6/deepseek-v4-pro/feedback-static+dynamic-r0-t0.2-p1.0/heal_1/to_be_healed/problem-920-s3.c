#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void **values;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

/* Possible weaknesses found:
 *  Parameter 'value' can be declared as pointer to const [constParameterPointer]
 */
static bool is_none(void *value) {
    return value == NULL;
}

static bool tuple_has_all_none(Tuple *tuple) {
    if (tuple == NULL || tuple->values == NULL) {
        return true;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (!is_none(tuple->values[i])) {
            return false;
        }
    }
    
    return true;
}

static void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

TupleList remove_all_none_tuples(TupleList *list) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;
    
    if (list == NULL || list->tuples == NULL || list->count == 0) {
        return result;
    }
    
    result.tuples = (Tuple *)malloc(list->count * sizeof(Tuple));
    if (result.tuples == NULL) {
        return result;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        if (!tuple_has_all_none(&list->tuples[i])) {
            result.tuples[result.count] = list->tuples[i];
            result.count++;
        } else {
            free_tuple(&list->tuples[i]);
        }
    }
    
    if (result.count == 0) {
        free(result.tuples);
        result.tuples = NULL;
    } else if (result.count < list->count) {
        Tuple *temp = (Tuple *)realloc(result.tuples, result.count * sizeof(Tuple));
        if (temp != NULL) {
            result.tuples = temp;
        }
    }
    
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    
    return result;
}

int main(void) {
    TupleList list;
    list.count = 4;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (list.tuples == NULL) {
        return 1;
    }
    
    list.tuples[0].size = 3;
    list.tuples[0].values = (void **)malloc(3 * sizeof(void *));
    list.tuples[0].values[0] = NULL;
    list.tuples[0].values[1] = NULL;
    list.tuples[0].values[2] = NULL;
    
    list.tuples[1].size = 2;
    list.tuples[1].values = (void **)malloc(2 * sizeof(void *));
    list.tuples[1].values[0] = (void *)1;
    list.tuples[1].values[1] = NULL;
    
    list.tuples[2].size = 2;
    list.tuples[2].values = (void **)malloc(2 * sizeof(void *));
    list.tuples[2].values[0] = NULL;
    list.tuples[2].values[1] = NULL;
    
    list.tuples[3].size = 1;
    list.tuples[3].values = (void **)malloc(1 * sizeof(void *));
    list.tuples[3].values[0] = (void *)2;
    
    TupleList result = remove_all_none_tuples(&list);
    
    for (size_t i = 0; i < result.count; i++) {
        for (size_t j = 0; j < result.tuples[i].size; j++) {
            if (result.tuples[i].values[j] != NULL) {
                printf("%p ", result.tuples[i].values[j]);
            } else {
                printf("NULL ");
            }
        }
        printf("\n");
        free(result.tuples[i].values);
    }
    
    free(result.tuples);
    
    return 0;
}
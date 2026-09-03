#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void **values;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

bool is_none(const void *value) {
    return value == NULL;
}

bool tuple_has_all_none(const Tuple *tuple) {
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

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    free(tuple->values);
    free(tuple);
}

TupleList *remove_all_none_tuples(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return list;
    }
    
    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < list->size; read_index++) {
        if (!tuple_has_all_none(&list->tuples[read_index])) {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
            }
            write_index++;
        } else {
            free_tuple(&list->tuples[read_index]);
        }
    }
    
    list->size = write_index;
    
    if (write_index == 0) {
        free(list->tuples);
        list->tuples = NULL;
    } else {
        Tuple *new_tuples = realloc(list->tuples, write_index * sizeof(Tuple));
        if (new_tuples != NULL) {
            list->tuples = new_tuples;
        }
    }
    
    return list;
}

Tuple *create_tuple(size_t size) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->values = calloc(size, sizeof(void *));
    if (tuple->values == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

TupleList *create_tuple_list(size_t size) {
    TupleList *list = malloc(sizeof(TupleList));
    if (list == NULL) {
        return NULL;
    }
    
    list->tuples = calloc(size, sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return NULL;
    }
    
    list->size = size;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    
    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->tuples[i].values);
        }
        free(list->tuples);
    }
    
    free(list);
}

int main(void) {
    TupleList *list = create_tuple_list(4);
    if (list == NULL) {
        return 1;
    }
    
    Tuple *tuple0 = create_tuple(3);
    if (tuple0 == NULL) {
        free_tuple_list(list);
        return 1;
    }
    tuple0->values[0] = NULL;
    tuple0->values[1] = NULL;
    tuple0->values[2] = NULL;
    list->tuples[0] = *tuple0;
    free(tuple0);
    
    Tuple *tuple1 = create_tuple(3);
    if (tuple1 == NULL) {
        free_tuple_list(list);
        return 1;
    }
    tuple1->values[0] = (void *)1;
    tuple1->values[1] = NULL;
    tuple1->values[2] = NULL;
    list->tuples[1] = *tuple1;
    free(tuple1);
    
    Tuple *tuple2 = create_tuple(3);
    if (tuple2 == NULL) {
        free_tuple_list(list);
        return 1;
    }
    tuple2->values[0] = NULL;
    tuple2->values[1] = NULL;
    tuple2->values[2] = NULL;
    list->tuples[2] = *tuple2;
    free(tuple2);
    
    Tuple *tuple3 = create_tuple(3);
    if (tuple3 == NULL) {
        free_tuple_list(list);
        return 1;
    }
    tuple3->values[0] = (void *)2;
    tuple3->values[1] = (void *)3;
    tuple3->values[2] = NULL;
    list->tuples[3] = *tuple3;
    free(tuple3);
    
    printf("Before removal: %zu tuples\n", list->size);
    
    remove_all_none_tuples(list);
    
    printf("After removal: %zu tuples\n", list->size);
    
    for (size_t i = 0; i < list->size; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            if (list->tuples[i].values[j] == NULL) {
                printf("NULL ");
            } else {
                printf("%p ", list->tuples[i].values[j]);
            }
        }
        printf("\n");
    }
    
    free_tuple_list(list);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
    int val3;
} Tuple;

typedef struct {
    Tuple *data;
    size_t len;
    size_t cap;
} TupleList;

TupleList tuple_list_create(size_t cap) {
    TupleList tl;
    tl.data = (Tuple *)malloc(cap * sizeof(Tuple));
    tl.len = 0;
    tl.cap = cap;
    return tl;
}

void tuple_list_push(TupleList *tl, Tuple t) {
    if (tl->len >= tl->cap) {
        tl->cap *= 2;
        Tuple *new_data = (Tuple *)realloc(tl->data, tl->cap * sizeof(Tuple));
        if (new_data) {
            tl->data = new_data;
        } else {
            free(tl->data);
            exit(EXIT_FAILURE);
        }
    }
    tl->data[tl->len++] = t;
}

void tuple_list_destroy(TupleList *tl) {
    free(tl->data);
    tl->data = NULL;
    tl->len = 0;
    tl->cap = 0;
}

TupleList remove_all_none_tuples(TupleList *tl) {
    TupleList result = tuple_list_create(tl->len > 0 ? tl->len : 1);
    for (size_t i = 0; i < tl->len; i++) {
        if (tl->data[i].val1 != 0 || tl->data[i].val2 != 0 || tl->data[i].val3 != 0) {
            tuple_list_push(&result, tl->data[i]);
        }
    }
    return result;
}

int main(void) {
    TupleList tl = tuple_list_create(4);
    
    tuple_list_push(&tl, (Tuple){0, 0, 0});
    tuple_list_push(&tl, (Tuple){1, 0, 0});
    tuple_list_push(&tl, (Tuple){0, 2, 0});
    tuple_list_push(&tl, (Tuple){0, 0, 3});
    tuple_list_push(&tl, (Tuple){0, 0, 0});
    tuple_list_push(&tl, (Tuple){4, 5, 6});
    
    TupleList filtered = remove_all_none_tuples(&tl);
    
    for (size_t i = 0; i < filtered.len; i++) {
        printf("(%d, %d, %d)\n", filtered.data[i].val1, filtered.data[i].val2, filtered.data[i].val3);
    }
    
    tuple_list_destroy(&tl);
    tuple_list_destroy(&filtered);
    
    return 0;
}
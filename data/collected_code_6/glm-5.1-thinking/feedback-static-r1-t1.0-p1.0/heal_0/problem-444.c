#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *items;
    int count;
} TupleList;

int tuple_init(Tuple *t, int size) {
    if (t == NULL || size < 0) {
        return -1;
    }
    t->size = size;
    if (size == 0) {
        t->elements = NULL;
        return 0;
    }
    t->elements = (int *)malloc(size * sizeof(int));
    if (t->elements == NULL) {
        return -1;
    }
    return 0;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

int tuple_list_init(TupleList *list, int count) {
    if (list == NULL || count < 0) {
        return -1;
    }
    list->count = count;
    if (count == 0) {
        list->items = NULL;
        return 0;
    }
    list->items = (Tuple *)malloc(count * sizeof(Tuple));
    if (list->items == NULL) {
        return -1;
    }
    memset(list->items, 0, count * sizeof(Tuple));
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (list != NULL && list->items != NULL) {
        for (int i = 0; i < list->count; i++) {
            tuple_free(&list->items[i]);
        }
        free(list->items);
        list->items = NULL;
        list->count = 0;
    }
}

int trim_tuples(TupleList *list, int k) {
    if (list == NULL || k < 0) {
        return -1;
    }
    if (list->items == NULL && list->count > 0) {
        return -1;
    }
    for (int i = 0; i < list->count; i++) {
        Tuple *t = &list->items[i];
        if (t == NULL) {
            return -1;
        }
        if (t->elements == NULL && t->size > 0) {
            return -1;
        }
        if (k > t->size / 2) {
            return -1;
        }
        int new_size = t->size - 2 * k;
        if (k > 0 && new_size > 0) {
            memmove(t->elements, t->elements + k, new_size * sizeof(int));
        }
        t->size = new_size;
    }
    return 0;
}

int main(void) {
    TupleList list;
    if (tuple_list_init(&list, 3) != 0) {
        return 1;
    }

    int sizes[] = {6, 8, 10};
    for (int i = 0; i < list.count; i++) {
        if (tuple_init(&list.items[i], sizes[i]) != 0) {
            tuple_list_free(&list);
            return 1;
        }
        for (int j = 0; j < sizes[i]; j++) {
            list.items[i].elements[j] = i * 10 + j;
        }
    }

    int k = 2;
    if (trim_tuples(&list, k) != 0) {
        tuple_list_free(&list);
        return 1;
    }

    for (int i = 0; i < list.count; i++) {
        for (int j = 0; j < list.items[i].size; j++) {
            printf("%d ", list.items[i].elements[j]);
        }
        printf("\n");
    }

    tuple_list_free(&list);
    return 0;
}
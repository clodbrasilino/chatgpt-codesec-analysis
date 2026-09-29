#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleArray;

void init_array(TupleArray *arr, size_t initial_capacity) {
    arr->items = malloc(initial_capacity * sizeof(Tuple));
    if (arr->items == NULL) {
        exit(EXIT_FAILURE);
    }
    arr->count = 0;
    arr->capacity = initial_capacity;
}

void append_array(TupleArray *arr, Tuple t) {
    if (arr->count == arr->capacity) {
        arr->capacity *= 2;
        Tuple *new_items = realloc(arr->items, arr->capacity * sizeof(Tuple));
        if (new_items == NULL) {
            free(arr->items);
            exit(EXIT_FAILURE);
        }
        arr->items = new_items;
    }
    arr->items[arr->count++] = t;
}

void free_array(TupleArray *arr) {
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

int tuples_equal(Tuple t1, Tuple t2) {
    return t1.a == t2.a && t1.b == t2.b;
}

void remove_matching_tuples(TupleArray *arr1, TupleArray *arr2) {
    for (size_t i = 0; i < arr1->count; ) {
        int found = 0;
        for (size_t j = 0; j < arr2->count; j++) {
            if (tuples_equal(arr1->items[i], arr2->items[j])) {
                found = 1;
                break;
            }
        }
        if (found) {
            for (size_t k = i; k < arr1->count - 1; k++) {
                arr1->items[k] = arr1->items[k + 1];
            }
            arr1->count--;
        } else {
            i++;
        }
    }
}

int main(void) {
    TupleArray arr1;
    TupleArray arr2;

    init_array(&arr1, 4);
    init_array(&arr2, 4);

    append_array(&arr1, (Tuple){1, 2});
    append_array(&arr1, (Tuple){3, 4});
    append_array(&arr1, (Tuple){5, 6});
    append_array(&arr1, (Tuple){7, 8});

    append_array(&arr2, (Tuple){3, 4});
    append_array(&arr2, (Tuple){7, 8});
    append_array(&arr2, (Tuple){9, 10});

    remove_matching_tuples(&arr1, &arr2);

    for (size_t i = 0; i < arr1.count; i++) {
        printf("(%d, %d)\n", arr1.items[i].a, arr1.items[i].b);
    }

    free_array(&arr1);
    free_array(&arr2);

    return 0;
}
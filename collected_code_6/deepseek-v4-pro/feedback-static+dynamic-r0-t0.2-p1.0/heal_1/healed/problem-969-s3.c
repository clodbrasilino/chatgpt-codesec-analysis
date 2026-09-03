#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    Tuple *items;
    int size;
    int capacity;
} TupleList;

void init_list(TupleList *list) {
    list->size = 0;
    list->capacity = 4;
    list->items = (Tuple *)malloc(list->capacity * sizeof(Tuple));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void free_list(TupleList *list) {
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

void add_tuple(TupleList *list, int key, int value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        Tuple *new_items = (Tuple *)realloc(list->items, list->capacity * sizeof(Tuple));
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(list->items);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
    }
    list->items[list->size].key = key;
    list->items[list->size].value = value;
    list->size++;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    return tuple_a->key - tuple_b->key;
}

TupleList join_tuples(TupleList *input) {
    TupleList result;
    init_list(&result);
    
    if (input->size == 0) {
        return result;
    }
    
    qsort(input->items, input->size, sizeof(Tuple), compare_tuples);
    
    int current_key = input->items[0].key;
    int current_value = input->items[0].value;
    
    for (int i = 1; i < input->size; i++) {
        if (input->items[i].key == current_key) {
            current_value += input->items[i].value;
        } else {
            add_tuple(&result, current_key, current_value);
            current_key = input->items[i].key;
            current_value = input->items[i].value;
        }
    }
    
    add_tuple(&result, current_key, current_value);
    
    return result;
}

int main(void) {
    TupleList input;
    init_list(&input);
    
    add_tuple(&input, 1, 10);
    add_tuple(&input, 2, 20);
    add_tuple(&input, 1, 30);
    add_tuple(&input, 3, 40);
    add_tuple(&input, 2, 50);
    add_tuple(&input, 1, 60);
    
    TupleList result = join_tuples(&input);
    
    for (int i = 0; i < result.size; i++) {
        printf("(%d, %d)\n", result.items[i].key, result.items[i].value);
    }
    
    free_list(&input);
    free_list(&result);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t size;
    size_t capacity;
} Tuple;

static void tuple_init(Tuple *tuple) {
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static void tuple_destroy(Tuple *tuple) {
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static int tuple_push(Tuple *tuple, int value) {
    if (tuple->size == tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 8 : tuple->capacity * 2;
        TupleItem *new_items = realloc(tuple->items, new_capacity * sizeof(TupleItem));
        if (new_items == NULL) {
            return 0;
        }
        tuple->items = new_items;
        tuple->capacity = new_capacity;
    }
    tuple->items[tuple->size].value = value;
    tuple->items[tuple->size].count = 0;
    tuple->size++;
    return 1;
}

static int count_repeated(const Tuple *tuple) {
    int repeated_count = 0;
    size_t i, j;
    
    for (i = 0; i < tuple->size; i++) {
        if (tuple->items[i].count != 0) {
            continue;
        }
        
        int current_count = 1;
        for (j = i + 1; j < tuple->size; j++) {
            if (tuple->items[j].count == 0 && tuple->items[i].value == tuple->items[j].value) {
                current_count++;
                tuple->items[j].count = current_count;
            }
        }
        tuple->items[i].count = current_count;
        
        if (current_count > 1) {
            repeated_count += current_count;
        }
    }
    
    return repeated_count;
}

int main(void) {
    int values[] = {1, 2, 3, 2, 4, 1, 2, 5, 1};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t i;
    Tuple tuple;
    int result;
    
    tuple_init(&tuple);
    
    for (i = 0; i < num_values; i++) {
        if (!tuple_push(&tuple, values[i])) {
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }
    }
    
    result = count_repeated(&tuple);
    printf("%d\n", result);
    
    tuple_destroy(&tuple);
    
    return EXIT_SUCCESS;
}
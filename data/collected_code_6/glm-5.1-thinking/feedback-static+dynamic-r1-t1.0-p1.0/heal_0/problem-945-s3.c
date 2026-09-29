#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleSet;

bool tuples_equal(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

TupleSet tuple_array_to_set(const Tuple *array, size_t array_size) {
    TupleSet set = {NULL, 0};
    
    if (array == NULL || array_size == 0) {
        return set;
    }
    
    set.items = (Tuple *)malloc(array_size * sizeof(Tuple));
    if (set.items == NULL) {
        return set;
    }
    
    for (size_t i = 0; i < array_size; ++i) {
        bool found = false;
        for (size_t j = 0; j < set.count; ++j) {
            if (tuples_equal(array[i], set.items[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            set.items[set.count] = array[i];
            set.count++;
        }
    }
    
    if (set.count == 0) {
        free(set.items);
        set.items = NULL;
        return set;
    }
    
    Tuple *temp = (Tuple *)realloc(set.items, set.count * sizeof(Tuple));
    if (temp != NULL) {
        set.items = temp;
    }
    
    return set;
}

int main(void) {
    Tuple input[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}};
    size_t input_size = sizeof(input) / sizeof(input[0]);
    
    TupleSet set = tuple_array_to_set(input, input_size);
    
    if (set.items != NULL) {
        for (size_t i = 0; i < set.count; ++i) {
            printf("(%d, %d)\n", set.items[i].first, set.items[i].second);
        }
        free(set.items);
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *items;
    int count;
    int capacity;
} TupleList;

TupleList* extract_symmetric_pairs(TupleList *input) {
    if (input == NULL || input->items == NULL) {
        return NULL;
    }

    TupleList *result = (TupleList *)malloc(sizeof(TupleList));
    if (result == NULL) {
        return NULL;
    }

    result->capacity = input->count > 0 ? input->count : 1;
    result->items = (Tuple *)malloc(result->capacity * sizeof(Tuple));
    if (result->items == NULL) {
        free(result);
        return NULL;
    }
    result->count = 0;

    for (int i = 0; i < input->count; i++) {
        for (int j = 0; j < input->count; j++) {
            if (i != j) {
                if (input->items[i].a == input->items[j].b && 
                    input->items[i].b == input->items[j].a) {
                    int is_duplicate = 0;
                    for (int k = 0; k < result->count; k++) {
                        if (result->items[k].a == input->items[i].a && 
                            result->items[k].b == input->items[i].b) {
                            is_duplicate = 1;
                            break;
                        }
                    }
                    if (!is_duplicate) {
                        if (result->count >= result->capacity) {
                            result->capacity *= 2;
                            Tuple *new_items = (Tuple *)realloc(result->items, result->capacity * sizeof(Tuple));
                            if (new_items == NULL) {
                                free(result->items);
                                free(result);
                                return NULL;
                            }
                            result->items = new_items;
                        }
                        result->items[result->count++] = input->items[i];
                    }
                    break;
                }
            }
        }
    }

    return result;
}

int main() {
    Tuple data[] = {{1, 2}, {3, 4}, {2, 1}, {5, 6}, {4, 3}, {7, 8}, {1, 2}};
    int data_count = sizeof(data) / sizeof(data[0]);

    TupleList input;
    input.items = data;
    input.count = data_count;
    input.capacity = data_count;

    TupleList *symmetric_pairs = extract_symmetric_pairs(&input);

    if (symmetric_pairs != NULL) {
        for (int i = 0; i < symmetric_pairs->count; i++) {
            printf("(%d, %d)\n", symmetric_pairs->items[i].a, symmetric_pairs->items[i].b);
        }
        free(symmetric_pairs->items);
        free(symmetric_pairs);
    }

    return 0;
}
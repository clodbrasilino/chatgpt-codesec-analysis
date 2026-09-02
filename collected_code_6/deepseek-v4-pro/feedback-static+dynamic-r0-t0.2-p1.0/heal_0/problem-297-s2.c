#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int is_integer;
    int value;
    struct NestedList **list;
    int list_size;
} NestedList;

typedef struct {
    int *data;
    int size;
    int capacity;
} FlatList;

void flat_list_init(FlatList *flat) {
    flat->data = NULL;
    flat->size = 0;
    flat->capacity = 0;
}

int flat_list_append(FlatList *flat, int value) {
    if (flat->size >= flat->capacity) {
        int new_capacity = flat->capacity == 0 ? 8 : flat->capacity * 2;
        int *new_data = (int *)realloc(flat->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        flat->data = new_data;
        flat->capacity = new_capacity;
    }
    flat->data[flat->size++] = value;
    return 1;
}

void flat_list_free(FlatList *flat) {
    free(flat->data);
    flat->data = NULL;
    flat->size = 0;
    flat->capacity = 0;
}

int flatten_helper(NestedList *nested, FlatList *flat) {
    if (nested == NULL) {
        return 0;
    }
    
    if (nested->is_integer) {
        return flat_list_append(flat, nested->value);
    }
    
    for (int i = 0; i < nested->list_size; i++) {
        if (!flatten_helper(nested->list[i], flat)) {
            return 0;
        }
    }
    
    return 1;
}

int flatten(NestedList *nested, FlatList *flat) {
    flat_list_init(flat);
    if (nested == NULL) {
        return 0;
    }
    return flatten_helper(nested, flat);
}

NestedList *create_integer(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 1;
    node->value = value;
    node->list = NULL;
    node->list_size = 0;
    return node;
}

NestedList *create_list(NestedList **items, int size) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->is_integer = 0;
    node->value = 0;
    node->list = items;
    node->list_size = size;
    return node;
}

void free_nested_list(NestedList *nested) {
    if (nested == NULL) {
        return;
    }
    if (!nested->is_integer) {
        for (int i = 0; i < nested->list_size; i++) {
            free_nested_list(nested->list[i]);
        }
        free(nested->list);
    }
    free(nested);
}

int main(void) {
    NestedList *n1 = create_integer(1);
    NestedList *n2 = create_integer(2);
    NestedList *n3 = create_integer(3);
    
    NestedList *inner_items[] = {n2, n3};
    NestedList *inner = create_list(inner_items, 2);
    
    NestedList *outer_items[] = {n1, inner};
    NestedList *outer = create_list(outer_items, 2);
    
    FlatList flat;
    if (flatten(outer, &flat)) {
        for (int i = 0; i < flat.size; i++) {
            printf("%d ", flat.data[i]);
        }
        printf("\n");
    } else {
        printf("Flattening failed\n");
    }
    
    flat_list_free(&flat);
    free_nested_list(outer);
    
    return 0;
}
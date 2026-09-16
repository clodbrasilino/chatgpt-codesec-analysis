#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Tuple {
    int64_t value;
    struct Tuple** children;
    size_t child_count;
    int is_leaf;
} Tuple;

Tuple* create_leaf(int64_t value) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->value = value;
    tuple->children = NULL;
    tuple->child_count = 0;
    tuple->is_leaf = 1;
    return tuple;
}

Tuple* create_nested(Tuple** children, size_t child_count) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->value = 0;
    tuple->children = children;
    tuple->child_count = child_count;
    tuple->is_leaf = 0;
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (!tuple) {
        return;
    }
    for (size_t i = 0; i < tuple->child_count; i++) {
        free_tuple(tuple->children[i]);
    }
    free(tuple->children);
    free(tuple);
}

int64_t subtract_elements(Tuple* tuple) {
    if (!tuple) {
        return 0;
    }
    if (tuple->is_leaf) {
        return tuple->value;
    }
    if (tuple->child_count == 0) {
        return 0;
    }
    int64_t result = subtract_elements(tuple->children[0]);
    for (size_t i = 1; i < tuple->child_count; i++) {
        result -= subtract_elements(tuple->children[i]);
    }
    return result;
}

int main(void) {
    Tuple* leaf1 = create_leaf(10);
    Tuple* leaf2 = create_leaf(3);
    Tuple* leaf3 = create_leaf(2);
    Tuple* leaf4 = create_leaf(5);
    
    if (!leaf1 || !leaf2 || !leaf3 || !leaf4) {
        free_tuple(leaf1);
        free_tuple(leaf2);
        free_tuple(leaf3);
        free_tuple(leaf4);
        return 1;
    }
    
    Tuple* nested1_children[] = {leaf1, leaf2};
    Tuple* nested1 = create_nested(nested1_children, 2);
    
    Tuple* nested2_children[] = {leaf3, leaf4};
    Tuple* nested2 = create_nested(nested2_children, 2);
    
    if (!nested1 || !nested2) {
        free_tuple(nested1);
        free_tuple(nested2);
        free_tuple(leaf1);
        free_tuple(leaf2);
        free_tuple(leaf3);
        free_tuple(leaf4);
        return 1;
    }
    
    Tuple* root_children[] = {nested1, nested2};
    Tuple* root = create_nested(root_children, 2);
    
    if (!root) {
        free_tuple(root);
        free_tuple(nested1);
        free_tuple(nested2);
        free_tuple(leaf1);
        free_tuple(leaf2);
        free_tuple(leaf3);
        free_tuple(leaf4);
        return 1;
    }
    
    int64_t result = subtract_elements(root);
    printf("%lld\n", (long long)result);
    
    free_tuple(root);
    
    return 0;
}
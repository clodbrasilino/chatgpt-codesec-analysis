#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int value;
    struct Tuple **children;
    int child_count;
} Tuple;

Tuple *create_tuple(int value, Tuple **children, int child_count) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) return NULL;
    t->value = value;
    t->children = children;
    t->child_count = child_count;
    return t;
}

void free_tuple(Tuple *t) {
    if (t == NULL) return;
    for (int i = 0; i < t->child_count; i++) {
        free_tuple(t->children[i]);
    }
    free(t->children);
    free(t);
}

int subtract_nested_tuples(Tuple *t) {
    if (t == NULL) return 0;
    int result = t->value;
    for (int i = 0; i < t->child_count; i++) {
        if (t->children[i] != NULL) {
            result -= subtract_nested_tuples(t->children[i]);
        }
    }
    return result;
}

int main() {
    Tuple *leaf1 = create_tuple(10, NULL, 0);
    Tuple *leaf2 = create_tuple(20, NULL, 0);
    Tuple *leaf3 = create_tuple(30, NULL, 0);
    
    Tuple *child1 = create_tuple(100, NULL, 0);
    Tuple *child2 = create_tuple(200, NULL, 0);
    
    Tuple **children_level2 = (Tuple **)malloc(2 * sizeof(Tuple *));
    children_level2[0] = child1;
    children_level2[1] = child2;
    Tuple *nested = create_tuple(50, children_level2, 2);
    
    Tuple **children_level1 = (Tuple **)malloc(3 * sizeof(Tuple *));
    children_level1[0] = leaf1;
    children_level1[1] = leaf2;
    children_level1[2] = nested;
    
    Tuple *root = create_tuple(500, children_level1, 3);
    
    int result = subtract_nested_tuples(root);
    printf("%d\n", result);
    
    free_tuple(root);
    
    Tuple **empty_children = (Tuple **)malloc(1 * sizeof(Tuple *));
    empty_children[0] = leaf3;
    Tuple *single = create_tuple(50, empty_children, 1);
    result = subtract_nested_tuples(single);
    printf("%d\n", result);
    
    free_tuple(single);
    free_tuple(leaf3);
    
    return 0;
}
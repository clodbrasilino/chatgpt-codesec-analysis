#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int value;
    struct NestedList **children;
    size_t child_count;
    int is_leaf;
} NestedList;

NestedList *create_leaf(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->children = NULL;
    node->child_count = 0;
    node->is_leaf = 1;
    return node;
}

NestedList *create_list(NestedList **children, size_t count) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->value = 0;
    node->children = children;
    node->child_count = count;
    node->is_leaf = 0;
    return node;
}

int is_equal(NestedList *a, NestedList *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->is_leaf != b->is_leaf) {
        return 0;
    }
    if (a->is_leaf) {
        return a->value == b->value;
    }
    if (a->child_count != b->child_count) {
        return 0;
    }
    for (size_t i = 0; i < a->child_count; i++) {
        if (!is_equal(a->children[i], b->children[i])) {
            return 0;
        }
    }
    return 1;
}

int is_subset(NestedList *sub, NestedList *super) {
    if (sub == NULL || super == NULL) {
        return 0;
    }
    if (sub->is_leaf) {
        if (super->is_leaf) {
            return sub->value == super->value;
        }
        for (size_t i = 0; i < super->child_count; i++) {
            if (is_subset(sub, super->children[i])) {
                return 1;
            }
        }
        return 0;
    }
    if (super->is_leaf) {
        return 0;
    }
    for (size_t i = 0; i < sub->child_count; i++) {
        int found = 0;
        for (size_t j = 0; j < super->child_count; j++) {
            if (is_subset(sub->children[i], super->children[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

void free_list(NestedList *node) {
    if (node == NULL) {
        return;
    }
    if (!node->is_leaf && node->children != NULL) {
        for (size_t i = 0; i < node->child_count; i++) {
            free_list(node->children[i]);
        }
        free(node->children);
    }
    free(node);
}

int main(void) {
    NestedList **sub_children = (NestedList **)malloc(2 * sizeof(NestedList *));
    if (sub_children == NULL) {
        return EXIT_FAILURE;
    }
    sub_children[0] = create_leaf(1);
    sub_children[1] = create_leaf(2);
    if (sub_children[0] == NULL || sub_children[1] == NULL) {
        free_list(sub_children[0]);
        free_list(sub_children[1]);
        free(sub_children);
        return EXIT_FAILURE;
    }
    NestedList *sub = create_list(sub_children, 2);
    if (sub == NULL) {
        free_list(sub_children[0]);
        free_list(sub_children[1]);
        free(sub_children);
        return EXIT_FAILURE;
    }

    NestedList **inner_children = (NestedList **)malloc(2 * sizeof(NestedList *));
    if (inner_children == NULL) {
        free_list(sub);
        return EXIT_FAILURE;
    }
    inner_children[0] = create_leaf(1);
    inner_children[1] = create_leaf(2);
    if (inner_children[0] == NULL || inner_children[1] == NULL) {
        free_list(inner_children[0]);
        free_list(inner_children[1]);
        free(inner_children);
        free_list(sub);
        return EXIT_FAILURE;
    }
    NestedList *inner = create_list(inner_children, 2);
    if (inner == NULL) {
        free_list(inner_children[0]);
        free_list(inner_children[1]);
        free(inner_children);
        free_list(sub);
        return EXIT_FAILURE;
    }

    NestedList **super_children = (NestedList **)malloc(2 * sizeof(NestedList *));
    if (super_children == NULL) {
        free_list(inner);
        free_list(sub);
        return EXIT_FAILURE;
    }
    super_children[0] = inner;
    super_children[1] = create_leaf(3);
    if (super_children[1] == NULL) {
        free_list(inner);
        free(super_children);
        free_list(sub);
        return EXIT_FAILURE;
    }
    NestedList *super = create_list(super_children, 2);
    if (super == NULL) {
        free_list(inner);
        free_list(super_children[1]);
        free(super_children);
        free_list(sub);
        return EXIT_FAILURE;
    }

    if (is_subset(sub, super)) {
        printf("Subset\n");
    } else {
        printf("Not subset\n");
    }

    free_list(sub);
    free_list(super);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int is_list;
    int value;
    struct Node **children;
    size_t child_count;
    size_t capacity;
} Node;

static Node *create_node(int is_list, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->is_list = is_list;
    node->value = value;
    node->children = NULL;
    node->child_count = 0;
    node->capacity = 0;
    return node;
}

static int add_child(Node *parent, Node *child) {
    if (parent == NULL || child == NULL) {
        return 0;
    }
    if (parent->child_count == parent->capacity) {
        size_t new_capacity = (parent->capacity == 0) ? 4 : parent->capacity * 2;
        Node **new_children = (Node **)realloc(parent->children, new_capacity * sizeof(Node *));
        if (new_children == NULL) {
            return 0;
        }
        parent->children = new_children;
        parent->capacity = new_capacity;
    }
    parent->children[parent->child_count] = child;
    parent->child_count++;
    return 1;
}

static void free_node(Node *node) {
    if (node == NULL) {
        return;
    }
    if (node->children != NULL) {
        size_t i;
        for (i = 0; i < node->child_count; i++) {
            free_node(node->children[i]);
        }
        free(node->children);
    }
    free(node);
}

static int nodes_equal(const Node *a, const Node *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->is_list != b->is_list) {
        return 0;
    }
    if (!a->is_list) {
        return a->value == b->value;
    }
    if (a->child_count != b->child_count) {
        return 0;
    }
    size_t i;
    for (i = 0; i < a->child_count; i++) {
        if (!nodes_equal(a->children[i], b->children[i])) {
            return 0;
        }
    }
    return 1;
}

static int is_subset_helper(const Node *sub, const Node *super, int *matched) {
    if (sub == NULL || super == NULL || matched == NULL) {
        return 0;
    }
    if (!sub->is_list) {
        return 0;
    }
    if (!super->is_list) {
        return 0;
    }
    size_t i, j;
    for (i = 0; i < sub->child_count; i++) {
        const Node *sub_child = sub->children[i];
        int found = 0;
        if (sub_child->is_list) {
            for (j = 0; j < super->child_count; j++) {
                if (!matched[j] && super->children[j]->is_list) {
                    if (is_subset_helper(sub_child, super->children[j], matched)) {
                        found = 1;
                        break;
                    }
                }
            }
        } else {
            for (j = 0; j < super->child_count; j++) {
                if (!matched[j] && !super->children[j]->is_list && 
                    super->children[j]->value == sub_child->value) {
                    matched[j] = 1;
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int is_subset(const Node *sub, const Node *super) {
    if (sub == NULL || super == NULL) {
        return 0;
    }
    if (!sub->is_list || !super->is_list) {
        return 0;
    }
    if (sub->child_count > super->child_count) {
        return 0;
    }
    int *matched = (int *)calloc(super->child_count, sizeof(int));
    if (matched == NULL) {
        return 0;
    }
    int result = is_subset_helper(sub, super, matched);
    free(matched);
    return result;
}

static Node *build_list_1(void) {
    Node *root = create_node(1, 0);
    Node *child1 = create_node(0, 1);
    Node *child2 = create_node(1, 0);
    Node *child2_1 = create_node(0, 2);
    Node *child2_2 = create_node(0, 3);
    Node *child3 = create_node(0, 4);
    
    if (root == NULL || child1 == NULL || child2 == NULL || 
        child2_1 == NULL || child2_2 == NULL || child3 == NULL) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        free_node(child3);
        return NULL;
    }
    
    if (!add_child(child2, child2_1) || !add_child(child2, child2_2) ||
        !add_child(root, child1) || !add_child(root, child2) || 
        !add_child(root, child3)) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        free_node(child3);
        return NULL;
    }
    
    return root;
}

static Node *build_list_2(void) {
    Node *root = create_node(1, 0);
    Node *child1 = create_node(0, 1);
    Node *child2 = create_node(1, 0);
    Node *child2_1 = create_node(0, 2);
    Node *child2_2 = create_node(0, 3);
    Node *child3 = create_node(0, 4);
    Node *child4 = create_node(0, 5);
    
    if (root == NULL || child1 == NULL || child2 == NULL || 
        child2_1 == NULL || child2_2 == NULL || child3 == NULL || child4 == NULL) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        free_node(child3);
        free_node(child4);
        return NULL;
    }
    
    if (!add_child(child2, child2_1) || !add_child(child2, child2_2) ||
        !add_child(root, child1) || !add_child(root, child2) || 
        !add_child(root, child3) || !add_child(root, child4)) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        free_node(child3);
        free_node(child4);
        return NULL;
    }
    
    return root;
}

static Node *build_list_3(void) {
    Node *root = create_node(1, 0);
    Node *child1 = create_node(0, 1);
    Node *child2 = create_node(1, 0);
    Node *child2_1 = create_node(0, 2);
    Node *child2_2 = create_node(0, 6);
    
    if (root == NULL || child1 == NULL || child2 == NULL || 
        child2_1 == NULL || child2_2 == NULL) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        return NULL;
    }
    
    if (!add_child(child2, child2_1) || !add_child(child2, child2_2) ||
        !add_child(root, child1) || !add_child(root, child2)) {
        free_node(root);
        free_node(child1);
        free_node(child2);
        free_node(child2_1);
        free_node(child2_2);
        return NULL;
    }
    
    return root;
}

int main(void) {
    Node *list1 = build_list_1();
    Node *list2 = build_list_2();
    Node *list3 = build_list_3();
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_node(list1);
        free_node(list2);
        free_node(list3);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("List1 is subset of List2: %s\n", is_subset(list1, list2) ? "true" : "false");
    printf("List3 is subset of List2: %s\n", is_subset(list3, list2) ? "true" : "false");
    printf("List1 is subset of List1: %s\n", is_subset(list1, list1) ? "true" : "false");
    
    free_node(list1);
    free_node(list2);
    free_node(list3);
    
    return EXIT_SUCCESS;
}
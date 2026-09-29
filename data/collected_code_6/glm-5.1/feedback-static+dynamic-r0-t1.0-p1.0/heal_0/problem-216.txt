#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    bool is_list;
    union {
        int integer;
        struct {
            struct Node* items;
            int count;
        } list;
    } data;
} Node;

bool is_subset(const Node* sub, const Node* super) {
    if (!sub || !super) return false;
    if (!sub->is_list && !super->is_list) return sub->data.integer == super->data.integer;
    if (!sub->is_list && super->is_list) {
        for (int i = 0; i < super->data.list.count; ++i) {
            if (is_subset(sub, &super->data.list.items[i])) return true;
        }
        return false;
    }
    if (sub->is_list && !super->is_list) return false;
    for (int i = 0; i < sub->data.list.count; ++i) {
        bool found = false;
        for (int j = 0; j < super->data.list.count; ++j) {
            if (is_subset(&sub->data.list.items[i], &super->data.list.items[j])) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

void free_tree(Node* node) {
    if (!node) return;
    if (node->is_list) {
        for (int i = 0; i < node->data.list.count; ++i) {
            free_tree(&node->data.list.items[i]);
        }
        free(node->data.list.items);
    }
}

int main() {
    Node sub_nodes[2] = {
        {.is_list = false, .data.integer = 1},
        {.is_list = false, .data.integer = 3}
    };
    Node sub = {.is_list = true, .data.list = {.items = sub_nodes, .count = 2}};

    Node inner_nodes[3] = {
        {.is_list = false, .data.integer = 1},
        {.is_list = false, .data.integer = 2},
        {.is_list = false, .data.integer = 3}
    };
    Node inner = {.is_list = true, .data.list = {.items = inner_nodes, .count = 3}};
    
    Node super_nodes[2] = {
        {.is_list = false, .data.integer = 5},
        inner
    };
    Node super = {.is_list = true, .data.list = {.items = super_nodes, .count = 2}};

    if (is_subset(&sub, &super)) {
        printf("Subset\n");
    } else {
        printf("Not a subset\n");
    }

    free_tree(&sub);
    free_tree(&super);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { DICT_NODE, VALUE_NODE } NodeType;

typedef struct DictNode {
    char *key;
    NodeType type;
    union {
        struct DictNode *child;
        int value;
    } data;
    struct DictNode *next;
} DictNode;

DictNode *create_value_node(const char *key, int value) {
    DictNode *node = (DictNode *)malloc(sizeof(DictNode));
    if (!node) return NULL;
    node->key = strdup(key);
    if (!node->key) { free(node); return NULL; }
    node->type = VALUE_NODE;
    node->data.value = value;
    node->next = NULL;
    return node;
}

DictNode *create_dict_node(const char *key, DictNode *child) {
    DictNode *node = (DictNode *)malloc(sizeof(DictNode));
    if (!node) return NULL;
    node->key = strdup(key);
    if (!node->key) { free(node); return NULL; }
    node->type = DICT_NODE;
    node->data.child = child;
    node->next = NULL;
    return node;
}

void free_dict(DictNode *node) {
    if (!node) return;
    free(node->key);
    if (node->type == DICT_NODE) {
        free_dict(node->data.child);
    }
    free_dict(node->next);
    free(node);
}

int find_depth(DictNode *node) {
    if (!node) return 0;
    int max_depth = 0;
    DictNode *current = node;
    while (current) {
        if (current->type == DICT_NODE) {
            int child_depth = find_depth(current->data.child);
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
        current = current->next;
    }
    return 1 + max_depth;
}

int main() {
    DictNode *inner_dict = create_value_node("c", 30);
    if (!inner_dict) return 1;
    
    DictNode *mid_dict = create_dict_node("b", inner_dict);
    if (!mid_dict) { free_dict(inner_dict); return 1; }
    mid_dict->next = create_value_node("d", 40);
    if (!mid_dict->next) { free_dict(mid_dict); return 1; }

    DictNode *root = create_value_node("a", 10);
    if (!root) { free_dict(mid_dict); return 1; }
    root->next = create_dict_node("e", mid_dict);
    if (!root->next) { free_dict(root); return 1; }

    int depth = find_depth(root);
    printf("%d\n", depth);

    free_dict(root);
    return 0;
}
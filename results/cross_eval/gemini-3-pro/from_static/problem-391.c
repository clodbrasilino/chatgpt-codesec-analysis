#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char *key;
    void *value;
    int is_nested;
    struct DictNode *next;
} DictNode;

DictNode* create_node(const char *key) {
    DictNode *node = (DictNode *)malloc(sizeof(DictNode));
    if (!node) {
        return NULL;
    }
    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }
    node->value = NULL;
    node->is_nested = 0;
    node->next = NULL;
    return node;
}

void free_dict(DictNode *head) {
    DictNode *current = head;
    while (current != NULL) {
        DictNode *next = current->next;
        free(current->key);
        if (current->is_nested && current->value != NULL) {
            free_dict((DictNode *)current->value);
        } else if (current->value != NULL) {
            free(current->value);
        }
        free(current);
        current = next;
    }
}

DictNode* lists_to_nested_dict(char **keys, char **values, int len) {
    if (len <= 0 || !keys || !values) {
        return NULL;
    }

    DictNode *root = create_node(keys[0]);
    if (!root) {
        return NULL;
    }

    DictNode *current = root;
    for (int i = 1; i < len; i++) {
        DictNode *new_node = create_node(keys[i]);
        if (!new_node) {
            free_dict(root);
            return NULL;
        }
        current->is_nested = 1;
        current->value = new_node;
        current = new_node;
    }

    current->is_nested = 0;
    current->value = strdup(values[len - 1]);
    if (!current->value) {
        free_dict(root);
        return NULL;
    }

    return root;
}

void print_dict(DictNode *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s: ", node->key);
    
    if (node->is_nested) {
        printf("{\n");
        print_dict((DictNode *)node->value, depth + 1);
        for (int i = 0; i < depth; i++) printf("  ");
        printf("}\n");
    } else {
        printf("%s\n", (char *)node->value);
    }
}

int main(void) {
    char *keys[] = {"level1", "level2", "level3"};
    char *values[] = {"val1", "val2", "val3"};
    int len = sizeof(keys) / sizeof(keys[0]);

    DictNode *dict = lists_to_nested_dict(keys, values, len);
    
    if (dict) {
        printf("{\n");
        print_dict(dict, 1);
        printf("}\n");
        free_dict(dict);
    }

    return 0;
}
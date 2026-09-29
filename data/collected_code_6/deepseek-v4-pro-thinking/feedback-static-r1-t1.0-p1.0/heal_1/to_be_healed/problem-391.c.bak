#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char *key;
    int value;
    struct DictNode *child;
    struct DictNode *next;
} DictNode;

DictNode *create_node(const char *key, int value) {
    if (!key) return NULL;
    DictNode *node = malloc(sizeof(*node));
    if (!node) return NULL;
    node->key = malloc(strlen(key) + 1);
    if (!node->key) {
        free(node);
        return NULL;
    }
    strcpy(node->key, key);
    node->value = value;
    node->child = NULL;
    node->next = NULL;
    return node;
}

DictNode *find_node(DictNode *head, const char *key) {
    if (!head || !key) return NULL;
    DictNode *cur = head;
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void free_dict(DictNode *node) {
    while (node) {
        DictNode *next = node->next;
        free(node->key);
        free_dict(node->child);
        free(node);
        node = next;
    }
}

int insert_path(DictNode **root, char **keys, int depth, int value) {
    if (!root || !keys || depth <= 0 || !keys[0]) return 0;
    DictNode *node = find_node(*root, keys[0]);
    int created = 0;
    if (!node) {
        node = create_node(keys[0], 0);
        if (!node) return 0;
        node->next = *root;
        *root = node;
        created = 1;
    }
    if (depth == 1) {
        node->value = value;
        return 1;
    }
    if (!insert_path(&node->child, keys + 1, depth - 1, value)) {
        if (created) {
            *root = node->next;
            node->next = NULL;
            free(node->key);
            free(node);
        }
        return 0;
    }
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'values' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'depths' can be declared as pointer to const [constParameterPointer]
 */
DictNode *lists_to_nested_dict(char ***key_lists, int *depths, int *values, int count) {
    if (!key_lists || !depths || !values || count <= 0) return NULL;
    DictNode *dict = NULL;
    for (int i = 0; i < count; i++) {
        if (!insert_path(&dict, key_lists[i], depths[i], values[i])) {
            free_dict(dict);
            return NULL;
        }
    }
    return dict;
}

void print_dict(DictNode *node, int indent) {
    while (node) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("%s: ", node->key);
        if (node->child) {
            printf("{\n");
            print_dict(node->child, indent + 1);
            for (int i = 0; i < indent; i++) printf("  ");
            printf("}\n");
        } else {
            printf("%d\n", node->value);
        }
        node = node->next;
    }
}

int main(void) {
    char *keys1[] = {"a", "b", "c"};
    char *keys2[] = {"a", "b", "d"};
    char *keys3[] = {"x", "y"};
    char **key_lists[] = {keys1, keys2, keys3};
    int depths[] = {3, 3, 2};
    int values[] = {10, 20, 30};

    DictNode *dict = lists_to_nested_dict(key_lists, depths, values, 3);
    if (!dict) {
        return 1;
    }

    print_dict(dict, 0);
    free_dict(dict);
    return 0;
}
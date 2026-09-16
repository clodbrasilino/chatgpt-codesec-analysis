#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char **keys;
    size_t key_count;
    int value;
} KeyValueList;

typedef struct DictNode {
    char *key;
    int value;
    struct DictNode *child;
    struct DictNode *next;
} DictNode;

static DictNode *create_dict_node(const char *key, int value);
static void free_dict(DictNode *node);
static DictNode *find_child(DictNode *node, const char *key);
static DictNode *insert_path(DictNode **root, const KeyValueList *list);
static void print_dict(const DictNode *node, int depth);

static DictNode *create_dict_node(const char *key, int value) {
    DictNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->key = malloc(strlen(key) + 1);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    strcpy(node->key, key);
    node->value = value;
    node->child = NULL;
    node->next = NULL;

    return node;
}

static void free_dict(DictNode *node) {
    while (node != NULL) {
        DictNode *next = node->next;
        free_dict(node->child);
        free(node->key);
        free(node);
        node = next;
    }
}

static DictNode *find_child(DictNode *node, const char *key) {
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

static DictNode *insert_path(DictNode **root, const KeyValueList *list) {
    if (!root || !list || list->key_count == 0) return NULL;
    if (*root == NULL) {
        *root = create_dict_node("", 0);
        if (*root == NULL) return NULL;
    }

    DictNode *curr = *root;
    for (size_t i = 0; i < list->key_count; i++) {
        DictNode *child = find_child(curr->child, list->keys[i]);
        if (!child) {
            child = create_dict_node(list->keys[i], 0);
            if (!child) return NULL;
            child->next = curr->child;
            curr->child = child;
        }
        curr = child;
    }
    curr->value = list->value;
    return curr;
}

static void print_dict(const DictNode *node, int depth) {
    while (node) {
        if (node->key[0] != '\0') {
            for (int i = 0; i < depth; i++) printf("  ");
            printf("%s: %d\n", node->key, node->value);
        }
        if (node->child) {
            print_dict(node->child, depth + 1);
        }
        node = node->next;
    }
}

int main(void) {
    DictNode *root = NULL;

    const char *keys1[] = {"a", "b", "c"};
    KeyValueList kv1 = {keys1, 3, 42};
    insert_path(&root, &kv1);

    const char *keys2[] = {"a", "b", "d"};
    KeyValueList kv2 = {keys2, 3, 99};
    insert_path(&root, &kv2);

    const char *keys3[] = {"x", "y"};
    KeyValueList kv3 = {keys3, 2, 7};
    insert_path(&root, &kv3);

    print_dict(root, 0);
    free_dict(root);
    return 0;
}
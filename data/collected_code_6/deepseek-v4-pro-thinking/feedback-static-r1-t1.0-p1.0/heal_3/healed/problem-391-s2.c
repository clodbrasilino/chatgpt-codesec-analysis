#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 256

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
    size_t len = strnlen(key, MAX_KEY_LEN);
    if (len == MAX_KEY_LEN) {
        return NULL;
    }

    DictNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->key = malloc(len + 1);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    snprintf(node->key, len + 1, "%s", key);
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
    if (root == NULL || list == NULL || list->keys == NULL || list->key_count == 0) {
        return NULL;
    }

    if (*root == NULL) {
        *root = calloc(1, sizeof(DictNode));
        if (*root == NULL) {
            return NULL;
        }
    }

    DictNode *current = *root;
    for (size_t i = 0; i < list->key_count; i++) {
        DictNode *child = find_child(current->child, list->keys[i]);
        if (child == NULL) {
            DictNode *new_node = create_dict_node(list->keys[i], 0);
            if (new_node == NULL) {
                return NULL;
            }
            new_node->next = current->child;
            current->child = new_node;
            child = new_node;
        }
        current = child;
    }

    current->value = list->value;
    return current;
}

static void print_dict(const DictNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    while (node != NULL) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        if (node->key != NULL) {
            printf("%s: %d\n", node->key, node->value);
        } else {
            printf("(root)\n");
        }
        print_dict(node->child, depth + 1);
        node = node->next;
    }
}

int main(void) {
    DictNode *root = NULL;

    const char *keys1[] = {"a", "b", "c"};
    KeyValueList list1 = { keys1, 3, 42 };

    const char *keys2[] = {"a", "b", "d"};
    KeyValueList list2 = { keys2, 3, 7 };

    const char *keys3[] = {"a", "e"};
    KeyValueList list3 = { keys3, 2, 99 };

    insert_path(&root, &list1);
    insert_path(&root, &list2);
    insert_path(&root, &list3);

    print_dict(root, 0);

    free_dict(root);
    return 0;
}
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
    if (root == NULL || list == NULL || list->keys == NULL || list->key_count == 0) {
        return NULL;
    }

    DictNode **link = root;

    for (size_t i = 0; i < list->key_count; i++) {
        DictNode *node = find_child(*link, list->keys[i]);

        if (node == NULL) {
            node = create_dict_node(list->keys[i], 0);
            if (node == NULL) {
                return NULL;
            }

            DictNode **tail = link;
            while (*tail != NULL) {
                tail = &(*tail)->next;
            }
            *tail = node;
        }

        if (i == list->key_count - 1) {
            node->value = list->value;
            return node;
        }

        link = &node->child;
    }

    return NULL;
}

static void print_dict(const DictNode *node, int depth) {
    while (node != NULL) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s: %d\n", node->key, node->value);
        print_dict(node->child, depth + 1);
        node = node->next;
    }
}

int main(void) {
    DictNode *root = NULL;

    const char *keys1[] = {"a", "b", "c"};
    KeyValueList list1 = {keys1, 3, 42};
    insert_path(&root, &list1);

    const char *keys2[] = {"a", "d"};
    KeyValueList list2 = {keys2, 2, 7};
    insert_path(&root, &list2);

    const char *keys3[] = {"x", "y"};
    KeyValueList list3 = {keys3, 2, 99};
    insert_path(&root, &list3);

    print_dict(root, 0);
    free_dict(root);
    return 0;
}
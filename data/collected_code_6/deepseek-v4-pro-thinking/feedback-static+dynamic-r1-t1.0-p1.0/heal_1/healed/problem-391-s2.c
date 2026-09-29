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
    if (key == NULL) {
        return NULL;
    }

    DictNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    size_t len = strlen(key);
    node->key = malloc(len + 1);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->key, key, len + 1);
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
    DictNode *current = NULL;

    for (size_t i = 0; i < list->key_count; ++i) {
        const char *key = list->keys[i];
        DictNode *found = find_child(*link, key);

        if (found == NULL) {
            int node_value = (i == list->key_count - 1) ? list->value : 0;
            DictNode *new_node = create_dict_node(key, node_value);
            if (new_node == NULL) {
                return NULL;
            }
            new_node->next = *link;
            *link = new_node;
            found = new_node;
        } else {
            if (i == list->key_count - 1) {
                found->value = list->value;
            }
        }

        current = found;
        link = &(current->child);
    }

    return current;
}

static void print_dict(const DictNode *node, int depth) {
    while (node != NULL) {
        for (int i = 0; i < depth; ++i) {
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
    const char *keys2[] = {"a", "b", "d"};
    const char *keys3[] = {"a", "e"};
    const char *keys4[] = {"x", "y"};

    KeyValueList list1 = {keys1, 3, 10};
    KeyValueList list2 = {keys2, 3, 20};
    KeyValueList list3 = {keys3, 2, 30};
    KeyValueList list4 = {keys4, 2, 40};

    insert_path(&root, &list1);
    insert_path(&root, &list2);
    insert_path(&root, &list3);
    insert_path(&root, &list4);

    print_dict(root, 0);
    free_dict(root);

    return 0;
}
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_INTEGER,
    NODE_LIST
} NodeType;

typedef struct Node Node;

typedef struct {
    Node **items;
    size_t count;
} NodeList;

struct Node {
    NodeType type;
    union {
        int integer;
        NodeList list;
    } value;
};

static Node *node_create_integer(int value)
{
    Node *node = calloc(1, sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->type = NODE_INTEGER;
    node->value.integer = value;
    return node;
}

static Node *node_create_list(size_t count)
{
    Node *node = calloc(1, sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->type = NODE_LIST;
    node->value.list.count = count;

    if (count != 0) {
        if (count > SIZE_MAX / sizeof(*node->value.list.items)) {
            free(node);
            return NULL;
        }

        node->value.list.items =
            calloc(count, sizeof(*node->value.list.items));

        if (node->value.list.items == NULL) {
            free(node);
            return NULL;
        }
    }

    return node;
}

static bool node_list_set(Node *list, size_t index, Node *item)
{
    if (list == NULL || list->type != NODE_LIST || item == NULL ||
        index >= list->value.list.count ||
        list->value.list.items[index] != NULL) {
        return false;
    }

    list->value.list.items[index] = item;
    return true;
}

static void node_destroy(Node *node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_LIST) {
        for (size_t i = 0; i < node->value.list.count; ++i) {
            node_destroy(node->value.list.items[i]);
        }

        free(node->value.list.items);
    }

    free(node);
}

static bool node_equal(const Node *left, const Node *right)
{
    if (left == NULL || right == NULL || left->type != right->type) {
        return false;
    }

    if (left->type == NODE_INTEGER) {
        return left->value.integer == right->value.integer;
    }

    if (left->value.list.count != right->value.list.count) {
        return false;
    }

    for (size_t i = 0; i < left->value.list.count; ++i) {
        if (!node_equal(left->value.list.items[i],
                        right->value.list.items[i])) {
            return false;
        }
    }

    return true;
}

static bool nested_list_is_subset(const Node *subset, const Node *superset)
{
    if (subset == NULL || superset == NULL ||
        subset->type != NODE_LIST || superset->type != NODE_LIST) {
        return false;
    }

    if (subset->value.list.count > superset->value.list.count) {
        return false;
    }

    const size_t candidate_count = superset->value.list.count;

    if (candidate_count == 0) {
        return true;
    }

    if (candidate_count > SIZE_MAX / sizeof(bool)) {
        return false;
    }

    bool *used = calloc(candidate_count, sizeof(*used));

    if (used == NULL) {
        return false;
    }

    for (size_t i = 0; i < subset->value.list.count; ++i) {
        bool found = false;

        for (size_t j = 0; j < candidate_count; ++j) {
            if (!used[j] &&
                node_equal(subset->value.list.items[i],
                           superset->value.list.items[j])) {
                used[j] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            free(used);
            return false;
        }
    }

    free(used);
    return true;
}

static bool add_integer(Node *list, size_t index, int value)
{
    Node *item = node_create_integer(value);

    if (item == NULL) {
        return false;
    }

    if (!node_list_set(list, index, item)) {
        node_destroy(item);
        return false;
    }

    return true;
}

int main(void)
{
    Node *subset = NULL;
    Node *superset = NULL;
    Node *nested_subset = NULL;
    Node *nested_superset = NULL;
    int result = EXIT_FAILURE;

    subset = node_create_list(2);
    superset = node_create_list(3);
    nested_subset = node_create_list(2);
    nested_superset = node_create_list(2);

    if (subset == NULL || superset == NULL ||
        nested_subset == NULL || nested_superset == NULL) {
        goto cleanup;
    }

    if (!add_integer(nested_subset, 0, 2) ||
        !add_integer(nested_subset, 1, 3) ||
        !add_integer(nested_superset, 0, 2) ||
        !add_integer(nested_superset, 1, 3) ||
        !add_integer(subset, 0, 1)) {
        goto cleanup;
    }

    if (!node_list_set(subset, 1, nested_subset)) {
        goto cleanup;
    }
    nested_subset = NULL;

    if (!node_list_set(superset, 0, nested_superset)) {
        goto cleanup;
    }
    nested_superset = NULL;

    if (!add_integer(superset, 1, 4) ||
        !add_integer(superset, 2, 1)) {
        goto cleanup;
    }

    if (printf("%s\n",
               nested_list_is_subset(subset, superset) ? "true" : "false") < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    node_destroy(nested_subset);
    node_destroy(nested_superset);
    node_destroy(subset);
    node_destroy(superset);
    return result;
}
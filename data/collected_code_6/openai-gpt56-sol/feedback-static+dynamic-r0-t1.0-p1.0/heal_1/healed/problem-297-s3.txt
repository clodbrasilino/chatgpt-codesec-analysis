#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    NODE_INTEGER,
    NODE_LIST
} NodeType;

typedef struct Node Node;

struct Node {
    NodeType type;
    union {
        int integer;
        struct {
            Node **items;
            size_t count;
        } list;
    } value;
};

typedef struct {
    int *items;
    size_t count;
    size_t capacity;
} IntArray;

static Node *create_integer(int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->type = NODE_INTEGER;
    node->value.integer = value;
    return node;
}

static Node *create_list(Node **items, size_t count)
{
    Node *node;

    if (count > 0U && items == NULL) {
        return NULL;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->type = NODE_LIST;
    node->value.list.items = items;
    node->value.list.count = count;
    return node;
}

static void destroy_node(Node *node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_LIST) {
        for (size_t i = 0U; i < node->value.list.count; ++i) {
            destroy_node(node->value.list.items[i]);
        }
        free(node->value.list.items);
    }

    free(node);
}

static bool append_integer(IntArray *array, int value)
{
    if (array == NULL) {
        return false;
    }

    if (array->count == array->capacity) {
        size_t new_capacity;

        if (array->capacity == 0U) {
            new_capacity = 8U;
        } else {
            if (array->capacity > SIZE_MAX / 2U) {
                return false;
            }
            new_capacity = array->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*array->items)) {
            return false;
        }

        int *new_items = realloc(
            array->items,
            new_capacity * sizeof(*array->items)
        );

        if (new_items == NULL) {
            return false;
        }

        array->items = new_items;
        array->capacity = new_capacity;
    }

    array->items[array->count] = value;
    ++array->count;
    return true;
}

static bool flatten_node(const Node *node, IntArray *result)
{
    if (node == NULL || result == NULL) {
        return false;
    }

    switch (node->type) {
        case NODE_INTEGER:
            return append_integer(result, node->value.integer);

        case NODE_LIST:
            if (node->value.list.count > 0U &&
                node->value.list.items == NULL) {
                return false;
            }

            for (size_t i = 0U; i < node->value.list.count; ++i) {
                if (!flatten_node(node->value.list.items[i], result)) {
                    return false;
                }
            }
            return true;

        default:
            return false;
    }
}

static bool flatten(const Node *root, int **values, size_t *count)
{
    IntArray result = { NULL, 0U, 0U };

    if (values == NULL || count == NULL) {
        return false;
    }

    *values = NULL;
    *count = 0U;

    if (root == NULL) {
        return false;
    }

    if (!flatten_node(root, &result)) {
        free(result.items);
        return false;
    }

    *values = result.items;
    *count = result.count;
    return true;
}

static Node *build_example(void)
{
    Node **inner_items = calloc(2U, sizeof(*inner_items));
    Node **outer_items = NULL;
    Node *inner = NULL;
    Node *root = NULL;

    if (inner_items == NULL) {
        goto failure;
    }

    inner_items[0] = create_integer(2);
    if (inner_items[0] == NULL) {
        goto failure;
    }

    inner_items[1] = create_integer(3);
    if (inner_items[1] == NULL) {
        goto failure;
    }

    inner = create_list(inner_items, 2U);
    if (inner == NULL) {
        goto failure;
    }
    inner_items = NULL;

    outer_items = calloc(3U, sizeof(*outer_items));
    if (outer_items == NULL) {
        goto failure;
    }

    outer_items[0] = create_integer(1);
    if (outer_items[0] == NULL) {
        goto failure;
    }

    outer_items[1] = inner;
    inner = NULL;

    outer_items[2] = create_integer(4);
    if (outer_items[2] == NULL) {
        goto failure;
    }

    root = create_list(outer_items, 3U);
    if (root == NULL) {
        goto failure;
    }

    return root;

failure:
    if (outer_items != NULL) {
        for (size_t i = 0U; i < 3U; ++i) {
            destroy_node(outer_items[i]);
        }
        free(outer_items);
    }

    destroy_node(inner);

    if (inner_items != NULL) {
        for (size_t i = 0U; i < 2U; ++i) {
            destroy_node(inner_items[i]);
        }
        free(inner_items);
    }

    return NULL;
}

int main(void)
{
    Node *root = build_example();
    int *values = NULL;
    size_t count = 0U;
    int status = EXIT_FAILURE;

    if (root == NULL) {
        fputs("Failed to build the nested list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!flatten(root, &values, &count)) {
        fputs("Failed to flatten the nested list.\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", values[i]) < 0) {
            fputs("Failed to write output.\n", stderr);
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    destroy_node(root);
    return status;
}
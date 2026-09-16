#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    NODE_INTEGER,
    NODE_LIST
} NodeType;

typedef struct NestedList NestedList;

struct NestedList {
    NodeType type;
    int value;
    NestedList **children;
    size_t child_count;
    size_t child_capacity;
};

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntArray;

static NestedList *nested_list_create_integer(int value)
{
    NestedList *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_INTEGER;
    node->value = value;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    return node;
}

static NestedList *nested_list_create_list(void)
{
    NestedList *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_LIST;
    node->value = 0;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    return node;
}

static int nested_list_add(NestedList *list, NestedList *item)
{
    if (list == NULL || item == NULL || list->type != NODE_LIST) {
        return -1;
    }

    if (list->child_count == list->child_capacity) {
        size_t new_capacity = (list->child_capacity == 0) ? 4 : list->child_capacity * 2;
        NestedList **new_children;

        if (new_capacity < list->child_capacity ||
            new_capacity > SIZE_MAX / sizeof(*list->children)) {
            return -1;
        }
        new_children = realloc(list->children, new_capacity * sizeof(*list->children));
        if (new_children == NULL) {
            return -1;
        }
        list->children = new_children;
        list->child_capacity = new_capacity;
    }

    list->children[list->child_count] = item;
    list->child_count++;
    return 0;
}

static void nested_list_free(NestedList *node)
{
    size_t i;

    if (node == NULL) {
        return;
    }

    for (i = 0; i < node->child_count; i++) {
        nested_list_free(node->children[i]);
    }
    free(node->children);
    free(node);
}

static int int_array_append(IntArray *arr, int value)
{
    if (arr == NULL) {
        return -1;
    }

    if (arr->size == arr->capacity) {
        size_t new_capacity = (arr->capacity == 0) ? 8 : arr->capacity * 2;
        int *new_data;

        if (new_capacity < arr->capacity ||
            new_capacity > SIZE_MAX / sizeof(*arr->data)) {
            return -1;
        }
        new_data = realloc(arr->data, new_capacity * sizeof(*arr->data));
        if (new_data == NULL) {
            return -1;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->size] = value;
    arr->size++;
    return 0;
}

static int flatten_into(const NestedList *node, IntArray *result)
{
    size_t i;

    if (node == NULL || result == NULL) {
        return -1;
    }

    if (node->type == NODE_INTEGER) {
        return int_array_append(result, node->value);
    }

    for (i = 0; i < node->child_count; i++) {
        if (flatten_into(node->children[i], result) != 0) {
            return -1;
        }
    }
    return 0;
}

int flatten_nested_list(const NestedList *root, int **out_values, size_t *out_count)
{
    IntArray result = { NULL, 0, 0 };

    if (root == NULL || out_values == NULL || out_count == NULL) {
        return -1;
    }

    if (flatten_into(root, &result) != 0) {
        free(result.data);
        return -1;
    }

    *out_values = result.data;
    *out_count = result.size;
    return 0;
}

static int nested_list_add_integer(NestedList *list, int value)
{
    NestedList *node;

    if (list == NULL) {
        return -1;
    }

    node = nested_list_create_integer(value);
    if (node == NULL) {
        return -1;
    }

    if (nested_list_add(list, node) != 0) {
        nested_list_free(node);
        return -1;
    }
    return 0;
}

static NestedList *nested_list_add_sublist(NestedList *list)
{
    NestedList *node;

    if (list == NULL) {
        return NULL;
    }

    node = nested_list_create_list();
    if (node == NULL) {
        return NULL;
    }

    if (nested_list_add(list, node) != 0) {
        nested_list_free(node);
        return NULL;
    }
    return node;
}

int main(void)
{
    NestedList *root;
    NestedList *list_a;
    NestedList *list_b;
    NestedList *list_c;
    int *flat = NULL;
    size_t flat_count = 0;
    size_t i;
    int exit_code = EXIT_FAILURE;

    root = nested_list_create_list();
    if (root == NULL) {
        return EXIT_FAILURE;
    }

    list_a = nested_list_add_sublist(root);
    if (list_a == NULL) {
        goto cleanup;
    }
    if (nested_list_add_integer(list_a, 1) != 0) {
        goto cleanup;
    }
    if (nested_list_add_integer(list_a, 2) != 0) {
        goto cleanup;
    }
    if (nested_list_add_integer(root, 3) != 0) {
        goto cleanup;
    }
    list_b = nested_list_add_sublist(root);
    if (list_b == NULL) {
        goto cleanup;
    }
    if (nested_list_add_integer(list_b, 4) != 0) {
        goto cleanup;
    }
    list_c = nested_list_add_sublist(list_b);
    if (list_c == NULL) {
        goto cleanup;
    }
    if (nested_list_add_integer(list_c, 5) != 0) {
        goto cleanup;
    }
    if (nested_list_add_integer(list_c, 6) != 0) {
        goto cleanup;
    }

    if (flatten_nested_list(root, &flat, &flat_count) != 0) {
        goto cleanup;
    }

    for (i = 0; i < flat_count; i++) {
        if (printf("%d%s", flat[i], (i + 1 < flat_count) ? " " : "\n") < 0) {
            goto cleanup;
        }
    }

    exit_code = EXIT_SUCCESS;

cleanup:
    free(flat);
    nested_list_free(root);
    return exit_code;
}
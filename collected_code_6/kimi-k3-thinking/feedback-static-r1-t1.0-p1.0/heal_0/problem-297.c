#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    NODE_INT,
    NODE_LIST
} NodeType;

typedef struct NestedList NestedList;

struct NestedList {
    NodeType type;
    union {
        int value;
        struct {
            NestedList **items;
            size_t count;
            size_t capacity;
        } list;
    } data;
};

static void nested_list_destroy(NestedList *node);

static NestedList *nested_list_create_int(int value)
{
    NestedList *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_INT;
    node->data.value = value;
    return node;
}

static NestedList *nested_list_create_list(void)
{
    NestedList *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_LIST;
    node->data.list.items = NULL;
    node->data.list.count = 0U;
    node->data.list.capacity = 0U;
    return node;
}

static int nested_list_add_node(NestedList *list, NestedList *item)
{
    NestedList **new_items;
    size_t new_capacity;

    if ((list == NULL) || (item == NULL) || (list->type != NODE_LIST)) {
        return -1;
    }

    if (list->data.list.count == list->data.list.capacity) {
        if (list->data.list.capacity > (SIZE_MAX / 2U)) {
            return -1;
        }
        new_capacity = (list->data.list.capacity == 0U)
            ? 4U
            : (list->data.list.capacity * 2U);
        if (new_capacity > (SIZE_MAX / sizeof(*new_items))) {
            return -1;
        }
        new_items = realloc(list->data.list.items,
                            new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return -1;
        }
        list->data.list.items = new_items;
        list->data.list.capacity = new_capacity;
    }

    list->data.list.items[list->data.list.count] = item;
    list->data.list.count++;
    return 0;
}

static int nested_list_add_int(NestedList *list, int value)
{
    NestedList *node = nested_list_create_int(value);
    if (node == NULL) {
        return -1;
    }
    if (nested_list_add_node(list, node) != 0) {
        nested_list_destroy(node);
        return -1;
    }
    return 0;
}

static int nested_list_add_sublist(NestedList *list, NestedList **out_child)
{
    NestedList *node;

    if (out_child == NULL) {
        return -1;
    }

    node = nested_list_create_list();
    if (node == NULL) {
        return -1;
    }
    if (nested_list_add_node(list, node) != 0) {
        nested_list_destroy(node);
        return -1;
    }
    *out_child = node;
    return 0;
}

static void nested_list_destroy(NestedList *node)
{
    size_t i;

    if (node == NULL) {
        return;
    }

    if (node->type == NODE_LIST) {
        for (i = 0U; i < node->data.list.count; i++) {
            nested_list_destroy(node->data.list.items[i]);
        }
        free(node->data.list.items);
        node->data.list.items = NULL;
        node->data.list.count = 0U;
        node->data.list.capacity = 0U;
    }

    free(node);
}

static int count_values(const NestedList *node, size_t *total)
{
    size_t i;

    if ((node == NULL) || (total == NULL)) {
        return -1;
    }

    if (node->type == NODE_INT) {
        if (*total == SIZE_MAX) {
            return -1;
        }
        *total += 1U;
        return 0;
    }

    for (i = 0U; i < node->data.list.count; i++) {
        if (count_values(node->data.list.items[i], total) != 0) {
            return -1;
        }
    }

    return 0;
}

static int flatten_into(const NestedList *node, int *values,
                        size_t *index, size_t capacity)
{
    size_t i;

    if ((node == NULL) || (values == NULL) || (index == NULL)) {
        return -1;
    }

    if (node->type == NODE_INT) {
        if (*index >= capacity) {
            return -1;
        }
        values[*index] = node->data.value;
        *index += 1U;
        return 0;
    }

    for (i = 0U; i < node->data.list.count; i++) {
        if (flatten_into(node->data.list.items[i], values,
                         index, capacity) != 0) {
            return -1;
        }
    }

    return 0;
}

int nested_list_flatten(const NestedList *root, int **out_values,
                        size_t *out_size)
{
    int *values;
    size_t index = 0U;
    size_t total = 0U;

    if ((root == NULL) || (out_values == NULL) || (out_size == NULL)) {
        return -1;
    }

    *out_values = NULL;
    *out_size = 0U;

    if (count_values(root, &total) != 0) {
        return -1;
    }

    if (total == 0U) {
        return 0;
    }

    if (total > (SIZE_MAX / sizeof(*values))) {
        return -1;
    }

    values = malloc(total * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    if (flatten_into(root, values, &index, total) != 0) {
        free(values);
        return -1;
    }

    *out_values = values;
    *out_size = index;
    return 0;
}

int main(void)
{
    NestedList *root;
    NestedList *sub1 = NULL;
    NestedList *sub2 = NULL;
    NestedList *sub3 = NULL;
    int *flat = NULL;
    size_t size = 0U;
    size_t i;
    int rc = EXIT_SUCCESS;

    root = nested_list_create_list();
    if (root == NULL) {
        return EXIT_FAILURE;
    }

    if ((nested_list_add_sublist(root, &sub1) != 0) ||
        (nested_list_add_int(sub1, 1) != 0) ||
        (nested_list_add_int(sub1, 2) != 0) ||
        (nested_list_add_int(root, 3) != 0) ||
        (nested_list_add_sublist(root, &sub2) != 0) ||
        (nested_list_add_int(sub2, 4) != 0) ||
        (nested_list_add_sublist(sub2, &sub3) != 0) ||
        (nested_list_add_int(sub3, 5) != 0) ||
        (nested_list_add_int(sub3, 6) != 0)) {
        nested_list_destroy(root);
        return EXIT_FAILURE;
    }

    if (nested_list_flatten(root, &flat, &size) != 0) {
        nested_list_destroy(root);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < size; i++) {
        if (printf("%d ", flat[i]) < 0) {
            rc = EXIT_FAILURE;
            break;
        }
    }

    if ((rc == EXIT_SUCCESS) && (printf("\n") < 0)) {
        rc = EXIT_FAILURE;
    }

    free(flat);
    nested_list_destroy(root);
    return rc;
}
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    NODE_INT,
    NODE_LIST
} NodeType;

typedef struct NestedList {
    NodeType type;
    union {
        int value;
        struct {
            struct NestedList *items;
            size_t count;
        } list;
    } data;
} NestedList;

static int append_int(int **arr, size_t *count, size_t *capacity, int value)
{
    int *new_arr;
    size_t new_capacity;

    if (arr == NULL || count == NULL || capacity == NULL) {
        return -1;
    }
    if (*count >= *capacity) {
        new_capacity = (*capacity == 0) ? 8 : *capacity * 2;
        if (new_capacity < *capacity || new_capacity > SIZE_MAX / sizeof(**arr)) {
            return -1;
        }
        new_arr = realloc(*arr, new_capacity * sizeof(**arr));
        if (new_arr == NULL) {
            return -1;
        }
        *arr = new_arr;
        *capacity = new_capacity;
    }
    (*arr)[*count] = value;
    *count += 1;
    return 0;
}

static int flatten_node(const NestedList *node, int **arr, size_t *count, size_t *capacity)
{
    size_t i;

    if (node == NULL) {
        return -1;
    }
    if (node->type == NODE_INT) {
        return append_int(arr, count, capacity, node->data.value);
    }
    if (node->type == NODE_LIST) {
        if (node->data.list.count > 0 && node->data.list.items == NULL) {
            return -1;
        }
        for (i = 0; i < node->data.list.count; i++) {
            if (flatten_node(&node->data.list.items[i], arr, count, capacity) != 0) {
                return -1;
            }
        }
        return 0;
    }
    return -1;
}

int flatten(const NestedList *list, int **out, size_t *out_count)
{
    int *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;

    if (list == NULL || out == NULL || out_count == NULL) {
        return -1;
    }
    if (flatten_node(list, &arr, &count, &capacity) != 0) {
        free(arr);
        return -1;
    }
    *out = arr;
    *out_count = count;
    return 0;
}

static NestedList make_int(int value)
{
    NestedList node;

    node.type = NODE_INT;
    node.data.value = value;
    return node;
}

static int init_list(NestedList *node, size_t count)
{
    if (node == NULL) {
        return -1;
    }
    node->type = NODE_LIST;
    node->data.list.count = count;
    node->data.list.items = NULL;
    if (count == 0) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(*node->data.list.items)) {
        node->data.list.count = 0;
        return -1;
    }
    node->data.list.items = calloc(count, sizeof(*node->data.list.items));
    if (node->data.list.items == NULL) {
        node->data.list.count = 0;
        return -1;
    }
    return 0;
}

static void free_list(NestedList *node)
{
    size_t i;

    if (node == NULL) {
        return;
    }
    if (node->type == NODE_LIST) {
        for (i = 0; i < node->data.list.count; i++) {
            free_list(&node->data.list.items[i]);
        }
        free(node->data.list.items);
        node->data.list.items = NULL;
        node->data.list.count = 0;
    }
}

int main(void)
{
    NestedList root;
    NestedList *inner;
    NestedList *innermost;
    int *flat = NULL;
    size_t count = 0;
    size_t i;

    if (init_list(&root, 3) != 0) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }

    root.data.list.items[0] = make_int(1);
    root.data.list.items[2] = make_int(5);

    inner = &root.data.list.items[1];
    if (init_list(inner, 2) != 0) {
        fprintf(stderr, "Failed to create list\n");
        free_list(&root);
        return EXIT_FAILURE;
    }
    inner->data.list.items[0] = make_int(2);

    innermost = &inner->data.list.items[1];
    if (init_list(innermost, 2) != 0) {
        fprintf(stderr, "Failed to create list\n");
        free_list(&root);
        return EXIT_FAILURE;
    }
    innermost->data.list.items[0] = make_int(3);
    innermost->data.list.items[1] = make_int(4);

    if (flatten(&root, &flat, &count) != 0) {
        fprintf(stderr, "Failed to flatten list\n");
        free_list(&root);
        return EXIT_FAILURE;
    }

    printf("Flattened list: ");
    for (i = 0; i < count; i++) {
        printf("%d ", flat[i]);
    }
    printf("\n");

    free(flat);
    flat = NULL;
    free_list(&root);

    return EXIT_SUCCESS;
}
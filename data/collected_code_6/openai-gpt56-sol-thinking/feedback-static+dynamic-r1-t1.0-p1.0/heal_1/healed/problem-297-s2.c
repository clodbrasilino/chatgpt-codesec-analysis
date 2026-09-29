#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_VALUE,
    NODE_LIST
} NodeType;

typedef struct Node Node;

typedef struct {
    const Node *items;
    size_t length;
} NodeList;

struct Node {
    NodeType type;
    union {
        int value;
        NodeList list;
    } data;
};

typedef enum {
    FLATTEN_SUCCESS,
    FLATTEN_INVALID_ARGUMENT,
    FLATTEN_NO_MEMORY,
    FLATTEN_TOO_LARGE,
    FLATTEN_INVALID_NODE
} FlattenResult;

static FlattenResult reserve_node_stack(
    const Node ***buffer,
    size_t *capacity,
    size_t required)
{
    size_t maximum;
    size_t new_capacity;
    const Node **new_buffer;

    if (required <= *capacity) {
        return FLATTEN_SUCCESS;
    }

    maximum = SIZE_MAX / sizeof(**buffer);
    if (required > maximum) {
        return FLATTEN_TOO_LARGE;
    }

    new_capacity = (*capacity == 0)
        ? (maximum < 16 ? maximum : 16)
        : *capacity;

    while (new_capacity < required) {
        if (new_capacity > maximum / 2) {
            new_capacity = required;
        } else {
            new_capacity *= 2;
        }
    }

    new_buffer = realloc(*buffer, new_capacity * sizeof(**buffer));
    if (new_buffer == NULL) {
        return FLATTEN_NO_MEMORY;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;

    return FLATTEN_SUCCESS;
}

static FlattenResult reserve_values(
    int **buffer,
    size_t *capacity,
    size_t required)
{
    size_t maximum;
    size_t new_capacity;
    int *new_buffer;

    if (required <= *capacity) {
        return FLATTEN_SUCCESS;
    }

    maximum = SIZE_MAX / sizeof(**buffer);
    if (required > maximum) {
        return FLATTEN_TOO_LARGE;
    }

    new_capacity = (*capacity == 0)
        ? (maximum < 16 ? maximum : 16)
        : *capacity;

    while (new_capacity < required) {
        if (new_capacity > maximum / 2) {
            new_capacity = required;
        } else {
            new_capacity *= 2;
        }
    }

    new_buffer = realloc(*buffer, new_capacity * sizeof(**buffer));
    if (new_buffer == NULL) {
        return FLATTEN_NO_MEMORY;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;

    return FLATTEN_SUCCESS;
}

FlattenResult flatten_list(
    const Node *root,
    int **flattened_values,
    size_t *flattened_length)
{
    const Node **stack = NULL;
    int *values = NULL;
    size_t stack_length = 0;
    size_t stack_capacity = 0;
    size_t values_length = 0;
    size_t values_capacity = 0;
    FlattenResult result;

    if (root == NULL ||
        flattened_values == NULL ||
        flattened_length == NULL) {
        return FLATTEN_INVALID_ARGUMENT;
    }

    *flattened_values = NULL;
    *flattened_length = 0;

    result = reserve_node_stack(&stack, &stack_capacity, 1);
    if (result != FLATTEN_SUCCESS) {
        return result;
    }

    stack[stack_length++] = root;

    while (stack_length > 0) {
        const Node *node = stack[--stack_length];

        if (node->type == NODE_VALUE) {
            if (values_length == SIZE_MAX) {
                result = FLATTEN_TOO_LARGE;
                goto failure;
            }

            result = reserve_values(
                &values,
                &values_capacity,
                values_length + 1);

            if (result != FLATTEN_SUCCESS) {
                goto failure;
            }

            values[values_length++] = node->data.value;
        } else if (node->type == NODE_LIST) {
            const size_t list_length = node->data.list.length;
            const Node *items = node->data.list.items;

            if (list_length > 0 && items == NULL) {
                result = FLATTEN_INVALID_NODE;
                goto failure;
            }

            if (list_length > SIZE_MAX - stack_length) {
                result = FLATTEN_TOO_LARGE;
                goto failure;
            }

            result = reserve_node_stack(
                &stack,
                &stack_capacity,
                stack_length + list_length);

            if (result != FLATTEN_SUCCESS) {
                goto failure;
            }

            for (size_t i = list_length; i > 0; --i) {
                stack[stack_length++] = &items[i - 1];
            }
        } else {
            result = FLATTEN_INVALID_NODE;
            goto failure;
        }
    }

    free(stack);
    *flattened_values = values;
    *flattened_length = values_length;

    return FLATTEN_SUCCESS;

failure:
    free(stack);
    free(values);
    return result;
}

static const char *flatten_result_string(FlattenResult result)
{
    switch (result) {
        case FLATTEN_SUCCESS:
            return "success";
        case FLATTEN_INVALID_ARGUMENT:
            return "invalid argument";
        case FLATTEN_NO_MEMORY:
            return "memory allocation failed";
        case FLATTEN_TOO_LARGE:
            return "result is too large";
        case FLATTEN_INVALID_NODE:
            return "invalid node";
        default:
            return "unknown error";
    }
}

int main(void)
{
    Node deepest_items[] = {
        { .type = NODE_VALUE, .data.value = 4 },
        { .type = NODE_VALUE, .data.value = 5 }
    };

    Node middle_items[] = {
        { .type = NODE_VALUE, .data.value = 2 },
        {
            .type = NODE_LIST,
            .data.list = {
                .items = deepest_items,
                .length = sizeof(deepest_items) / sizeof(deepest_items[0])
            }
        },
        { .type = NODE_VALUE, .data.value = 6 }
    };

    Node root_items[] = {
        { .type = NODE_VALUE, .data.value = 1 },
        {
            .type = NODE_LIST,
            .data.list = {
                .items = middle_items,
                .length = sizeof(middle_items) / sizeof(middle_items[0])
            }
        },
        { .type = NODE_VALUE, .data.value = 7 }
    };

    Node root = {
        .type = NODE_LIST,
        .data.list = {
            .items = root_items,
            .length = sizeof(root_items) / sizeof(root_items[0])
        }
    };

    int *flattened = NULL;
    size_t flattened_length = 0;
    FlattenResult result = flatten_list(
        &root,
        &flattened,
        &flattened_length);

    if (result != FLATTEN_SUCCESS) {
        if (fprintf(
                stderr,
                "%s%s\n",
                "Flattening failed: ",
                flatten_result_string(result)) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < flattened_length; ++i) {
        if (i > 0 && putchar(' ') == EOF) {
            free(flattened);
            return EXIT_FAILURE;
        }

        if (printf("%d", flattened[i]) < 0) {
            free(flattened);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}
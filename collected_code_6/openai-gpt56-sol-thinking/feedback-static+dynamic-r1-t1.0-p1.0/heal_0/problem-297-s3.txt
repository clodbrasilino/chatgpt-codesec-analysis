#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_VALUE,
    NODE_LIST
} NodeType;

typedef struct Node Node;

struct Node {
    NodeType type;
    union {
        int value;
        const Node *children;
    } data;
    const Node *next;
};

typedef enum {
    FLATTEN_SUCCESS,
    FLATTEN_INVALID_ARGUMENT,
    FLATTEN_INVALID_NODE,
    FLATTEN_ALLOCATION_FAILURE
} FlattenResult;

static bool resize_array(void **array, size_t *capacity, size_t element_size,
                         size_t required)
{
    size_t new_capacity;
    void *new_array;

    if (array == NULL || capacity == NULL || element_size == 0U) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    if (required > SIZE_MAX / element_size) {
        return false;
    }

    new_capacity = (*capacity == 0U) ? 16U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity > SIZE_MAX / element_size) {
        return false;
    }

    new_array = realloc(*array, new_capacity * element_size);
    if (new_array == NULL) {
        return false;
    }

    *array = new_array;
    *capacity = new_capacity;
    return true;
}

static FlattenResult flatten_list(const Node *list, int **out_values,
                                  size_t *out_count)
{
    const Node *current;
    const Node **stack = NULL;
    int *values = NULL;
    size_t stack_size = 0U;
    size_t stack_capacity = 0U;
    size_t value_count = 0U;
    size_t value_capacity = 0U;

    if (out_values == NULL || out_count == NULL) {
        return FLATTEN_INVALID_ARGUMENT;
    }

    *out_values = NULL;
    *out_count = 0U;
    current = list;

    while (current != NULL || stack_size > 0U) {
        const Node *node;

        if (current == NULL) {
            current = stack[--stack_size];
        }

        node = current;
        current = node->next;

        if (node->type == NODE_VALUE) {
            if (!resize_array((void **)&values, &value_capacity,
                              sizeof(*values), value_count + 1U)) {
                free(stack);
                free(values);
                return FLATTEN_ALLOCATION_FAILURE;
            }

            values[value_count++] = node->data.value;
        } else if (node->type == NODE_LIST) {
            if (current != NULL) {
                if (!resize_array((void **)&stack, &stack_capacity,
                                  sizeof(*stack), stack_size + 1U)) {
                    free(stack);
                    free(values);
                    return FLATTEN_ALLOCATION_FAILURE;
                }

                stack[stack_size++] = current;
            }

            current = node->data.children;
        } else {
            free(stack);
            free(values);
            return FLATTEN_INVALID_NODE;
        }
    }

    free(stack);
    *out_values = values;
    *out_count = value_count;
    return FLATTEN_SUCCESS;
}

int main(void)
{
    const Node inner_four = {
        .type = NODE_VALUE,
        .data.value = 4,
        .next = NULL
    };
    const Node inner_three = {
        .type = NODE_VALUE,
        .data.value = 3,
        .next = &inner_four
    };
    const Node middle_five = {
        .type = NODE_VALUE,
        .data.value = 5,
        .next = NULL
    };
    const Node middle_nested = {
        .type = NODE_LIST,
        .data.children = &inner_three,
        .next = &middle_five
    };
    const Node middle_two = {
        .type = NODE_VALUE,
        .data.value = 2,
        .next = &middle_nested
    };
    const Node root_six = {
        .type = NODE_VALUE,
        .data.value = 6,
        .next = NULL
    };
    const Node root_nested = {
        .type = NODE_LIST,
        .data.children = &middle_two,
        .next = &root_six
    };
    const Node root_one = {
        .type = NODE_VALUE,
        .data.value = 1,
        .next = &root_nested
    };
    int *values = NULL;
    size_t count = 0U;
    size_t index;
    FlattenResult result;

    result = flatten_list(&root_one, &values, &count);
    if (result != FLATTEN_SUCCESS) {
        if (fputs("Failed to flatten the list.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        if (printf("%s%d", (index == 0U) ? "" : " ", values[index]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NESTED_VALUE,
    NESTED_LIST
} NestedItemType;

typedef struct NestedItem NestedItem;

typedef struct {
    const NestedItem *items;
    size_t count;
} NestedList;

struct NestedItem {
    NestedItemType type;
    union {
        int value;
        NestedList list;
    } data;
};

typedef struct {
    const NestedList *list;
    size_t index;
} FlattenFrame;

static bool reserve_memory(void **memory, size_t *capacity,
                           size_t required, size_t element_size)
{
    size_t maximum;
    size_t new_capacity;
    void *replacement;

    if (required <= *capacity) {
        return true;
    }

    if (element_size == 0) {
        return false;
    }

    maximum = SIZE_MAX / element_size;
    if (required > maximum) {
        return false;
    }

    new_capacity = *capacity == 0 ? 8 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > maximum / 2) {
            new_capacity = maximum;
        } else {
            new_capacity *= 2;
        }

        if (new_capacity < required && new_capacity == maximum) {
            return false;
        }
    }

    replacement = realloc(*memory, new_capacity * element_size);
    if (replacement == NULL) {
        return false;
    }

    *memory = replacement;
    *capacity = new_capacity;
    return true;
}

bool flatten(const NestedList *list, int **values, size_t *value_count)
{
    FlattenFrame *stack = NULL;
    size_t stack_size = 0;
    size_t stack_capacity = 0;
    int *result = NULL;
    size_t result_count = 0;
    size_t result_capacity = 0;
    bool success = false;

    if (list == NULL || values == NULL || value_count == NULL) {
        return false;
    }

    *values = NULL;
    *value_count = 0;

    if (list->count > 0 && list->items == NULL) {
        return false;
    }

    if (list->count == 0) {
        return true;
    }

    if (!reserve_memory((void **)&stack, &stack_capacity, 1,
                        sizeof(*stack))) {
        goto cleanup;
    }

    stack[0].list = list;
    stack[0].index = 0;
    stack_size = 1;

    while (stack_size > 0) {
        FlattenFrame *frame = &stack[stack_size - 1];
        const NestedItem *item;

        if (frame->index == frame->list->count) {
            --stack_size;
            continue;
        }

        item = &frame->list->items[frame->index++];

        if (item->type == NESTED_VALUE) {
            if (result_count == SIZE_MAX) {
                goto cleanup;
            }

            if (!reserve_memory((void **)&result, &result_capacity,
                                result_count + 1, sizeof(*result))) {
                goto cleanup;
            }

            result[result_count++] = item->data.value;
        } else if (item->type == NESTED_LIST) {
            const NestedList *child = &item->data.list;
            size_t i;

            if (child->count > 0 && child->items == NULL) {
                goto cleanup;
            }

            if (child->count == 0) {
                continue;
            }

            for (i = 0; i < stack_size; ++i) {
                if (stack[i].list == child) {
                    goto cleanup;
                }
            }

            if (stack_size == SIZE_MAX) {
                goto cleanup;
            }

            if (!reserve_memory((void **)&stack, &stack_capacity,
                                stack_size + 1, sizeof(*stack))) {
                goto cleanup;
            }

            stack[stack_size].list = child;
            stack[stack_size].index = 0;
            ++stack_size;
        } else {
            goto cleanup;
        }
    }

    *values = result;
    *value_count = result_count;
    result = NULL;
    success = true;

cleanup:
    free(result);
    free(stack);
    return success;
}

int main(void)
{
    const NestedItem inner_items[] = {
        { .type = NESTED_VALUE, .data.value = 3 },
        { .type = NESTED_VALUE, .data.value = 4 }
    };

    const NestedItem middle_items[] = {
        { .type = NESTED_VALUE, .data.value = 2 },
        {
            .type = NESTED_LIST,
            .data.list = {
                .items = inner_items,
                .count = sizeof(inner_items) / sizeof(inner_items[0])
            }
        },
        { .type = NESTED_VALUE, .data.value = 5 }
    };

    const NestedItem root_items[] = {
        { .type = NESTED_VALUE, .data.value = 1 },
        {
            .type = NESTED_LIST,
            .data.list = {
                .items = middle_items,
                .count = sizeof(middle_items) / sizeof(middle_items[0])
            }
        },
        { .type = NESTED_VALUE, .data.value = 6 }
    };

    const NestedList root = {
        .items = root_items,
        .count = sizeof(root_items) / sizeof(root_items[0])
    };

    int *values = NULL;
    size_t value_count = 0;
    size_t i;

    if (!flatten(&root, &values, &value_count)) {
        (void)fputs("Unable to flatten the nested list\n", stderr);
        return EXIT_FAILURE;
    }

    if (putchar('[') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    for (i = 0; i < value_count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%d", values[i]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (puts("]") == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}
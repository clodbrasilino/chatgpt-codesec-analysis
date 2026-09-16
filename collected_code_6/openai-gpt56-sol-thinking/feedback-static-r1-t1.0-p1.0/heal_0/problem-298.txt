#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NESTING_DEPTH 128U

typedef enum {
    NESTED_VALUE,
    NESTED_LIST
} NestedElementType;

typedef struct NestedElement NestedElement;

typedef struct {
    const NestedElement *items;
    size_t count;
} NestedList;

struct NestedElement {
    NestedElementType type;
    union {
        int value;
        NestedList list;
    } data;
};

static bool contains_value(const int *values, size_t count, int value)
{
    size_t i;

    for (i = 0U; i < count; ++i) {
        if (values[i] == value) {
            return true;
        }
    }

    return false;
}

static bool count_matches(const NestedList *nested,
                          const int *other,
                          size_t other_count,
                          size_t depth,
                          size_t *count)
{
    size_t i;

    if (nested == NULL || count == NULL || depth > MAX_NESTING_DEPTH) {
        return false;
    }

    if (nested->count > 0U && nested->items == NULL) {
        return false;
    }

    for (i = 0U; i < nested->count; ++i) {
        const NestedElement *element = &nested->items[i];

        if (element->type == NESTED_VALUE) {
            if (contains_value(other, other_count, element->data.value)) {
                if (*count == SIZE_MAX) {
                    return false;
                }
                ++(*count);
            }
        } else if (element->type == NESTED_LIST) {
            if (!count_matches(&element->data.list,
                               other,
                               other_count,
                               depth + 1U,
                               count)) {
                return false;
            }
        } else {
            return false;
        }
    }

    return true;
}

static bool store_matches(const NestedList *nested,
                          const int *other,
                          size_t other_count,
                          size_t depth,
                          int *result,
                          size_t capacity,
                          size_t *index)
{
    size_t i;

    if (nested == NULL || index == NULL || depth > MAX_NESTING_DEPTH) {
        return false;
    }

    if (nested->count > 0U && nested->items == NULL) {
        return false;
    }

    for (i = 0U; i < nested->count; ++i) {
        const NestedElement *element = &nested->items[i];

        if (element->type == NESTED_VALUE) {
            if (contains_value(other, other_count, element->data.value)) {
                if (*index >= capacity || result == NULL) {
                    return false;
                }
                result[*index] = element->data.value;
                ++(*index);
            }
        } else if (element->type == NESTED_LIST) {
            if (!store_matches(&element->data.list,
                               other,
                               other_count,
                               depth + 1U,
                               result,
                               capacity,
                               index)) {
                return false;
            }
        } else {
            return false;
        }
    }

    return true;
}

static bool find_present_elements(const NestedList *nested,
                                  const int *other,
                                  size_t other_count,
                                  int **result,
                                  size_t *result_count)
{
    int *matches;
    size_t count = 0U;
    size_t index = 0U;

    if (result == NULL || result_count == NULL) {
        return false;
    }

    *result = NULL;
    *result_count = 0U;

    if (nested == NULL || (other_count > 0U && other == NULL)) {
        return false;
    }

    if (!count_matches(nested, other, other_count, 0U, &count)) {
        return false;
    }

    if (count == 0U) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*matches)) {
        return false;
    }

    matches = malloc(count * sizeof(*matches));
    if (matches == NULL) {
        return false;
    }

    if (!store_matches(nested,
                       other,
                       other_count,
                       0U,
                       matches,
                       count,
                       &index) ||
        index != count) {
        free(matches);
        return false;
    }

    *result = matches;
    *result_count = count;
    return true;
}

int main(void)
{
    static const NestedElement inner_items[] = {
        { .type = NESTED_VALUE, .data.value = 5 },
        { .type = NESTED_VALUE, .data.value = 2 }
    };

    static const NestedElement middle_items[] = {
        { .type = NESTED_VALUE, .data.value = 3 },
        {
            .type = NESTED_LIST,
            .data.list = {
                .items = inner_items,
                .count = sizeof(inner_items) / sizeof(inner_items[0])
            }
        }
    };

    static const NestedElement root_items[] = {
        { .type = NESTED_VALUE, .data.value = 1 },
        { .type = NESTED_VALUE, .data.value = 2 },
        {
            .type = NESTED_LIST,
            .data.list = {
                .items = middle_items,
                .count = sizeof(middle_items) / sizeof(middle_items[0])
            }
        },
        { .type = NESTED_VALUE, .data.value = 4 }
    };

    static const int other[] = { 2, 4, 6 };
    const NestedList nested = {
        .items = root_items,
        .count = sizeof(root_items) / sizeof(root_items[0])
    };

    int *matches = NULL;
    size_t match_count = 0U;
    size_t i;

    if (!find_present_elements(&nested,
                               other,
                               sizeof(other) / sizeof(other[0]),
                               &matches,
                               &match_count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < match_count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", matches[i]) < 0) {
            free(matches);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(matches);
        return EXIT_FAILURE;
    }

    free(matches);
    return EXIT_SUCCESS;
}
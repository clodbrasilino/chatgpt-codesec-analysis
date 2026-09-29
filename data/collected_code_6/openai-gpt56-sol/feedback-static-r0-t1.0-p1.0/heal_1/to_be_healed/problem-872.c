#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_LIST
} ValueType;

typedef struct Value Value;

typedef struct {
    const Value *items;
    size_t length;
} List;

struct Value {
    ValueType type;
    union {
        int integer;
        List list;
    } data;
};

static bool value_equal(const Value *left, const Value *right);

static bool list_equal(const List *left, const List *right)
{
    size_t i;

    if (left == NULL || right == NULL) {
        return false;
    }

    if (left->length != right->length) {
        return false;
    }

    if ((left->length > 0U && left->items == NULL) ||
        (right->length > 0U && right->items == NULL)) {
        return false;
    }

    for (i = 0U; i < left->length; ++i) {
        if (!value_equal(&left->items[i], &right->items[i])) {
            return false;
        }
    }

    return true;
}

static bool value_equal(const Value *left, const Value *right)
{
    if (left == NULL || right == NULL || left->type != right->type) {
        return false;
    }

    switch (left->type) {
        case VALUE_INTEGER:
            return left->data.integer == right->data.integer;
        case VALUE_LIST:
            return list_equal(&left->data.list, &right->data.list);
        default:
            return false;
    }
}

static bool nested_list_is_subset(const List *subset, const List *superset)
{
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    bool found;

    if (subset == NULL || superset == NULL) {
        return false;
    }

    if ((subset->length > 0U && subset->items == NULL) ||
        (superset->length > 0U && superset->items == NULL)) {
        return false;
    }

    for (i = 0U; i < subset->length; ++i) {
        found = false;

        for (j = 0U; j < superset->length; ++j) {
            if (value_equal(&subset->items[i], &superset->items[j])) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const Value inner_subset_items[] = {
        { .type = VALUE_INTEGER, .data.integer = 2 },
        { .type = VALUE_INTEGER, .data.integer = 3 }
    };

    const Value inner_superset_items[] = {
        { .type = VALUE_INTEGER, .data.integer = 2 },
        { .type = VALUE_INTEGER, .data.integer = 3 }
    };

    const Value subset_items[] = {
        { .type = VALUE_INTEGER, .data.integer = 1 },
        {
            .type = VALUE_LIST,
            .data.list = {
                .items = inner_subset_items,
                .length = sizeof(inner_subset_items) /
                          sizeof(inner_subset_items[0])
            }
        }
    };

    const Value superset_items[] = {
        { .type = VALUE_INTEGER, .data.integer = 4 },
        {
            .type = VALUE_LIST,
            .data.list = {
                .items = inner_superset_items,
                .length = sizeof(inner_superset_items) /
                          sizeof(inner_superset_items[0])
            }
        },
        { .type = VALUE_INTEGER, .data.integer = 1 }
    };

    const List subset = {
        .items = subset_items,
        .length = sizeof(subset_items) / sizeof(subset_items[0])
    };

    const List superset = {
        .items = superset_items,
        .length = sizeof(superset_items) / sizeof(superset_items[0])
    };

    if (printf("%s\n",
               nested_list_is_subset(&subset, &superset)
                   ? "true"
                   : "false") < 0) {
        return 1;
    }

    return 0;
}
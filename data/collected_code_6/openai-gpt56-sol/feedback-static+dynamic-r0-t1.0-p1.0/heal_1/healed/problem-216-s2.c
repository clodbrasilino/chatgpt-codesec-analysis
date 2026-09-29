#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_LIST
} ValueType;

typedef struct Value Value;

typedef struct {
    Value *items;
    size_t length;
} List;

struct Value {
    ValueType type;
    union {
        int integer;
        List list;
    } data;
};

static Value make_integer(int number)
{
    Value value;

    value.type = VALUE_INTEGER;
    value.data.integer = number;

    return value;
}

static bool make_list(Value *value, size_t length)
{
    if (value == NULL) {
        return false;
    }

    value->type = VALUE_LIST;
    value->data.list.items = NULL;
    value->data.list.length = 0U;

    if (length == 0U) {
        return true;
    }

    if (length > SIZE_MAX / sizeof(*value->data.list.items)) {
        return false;
    }

    value->data.list.items =
        calloc(length, sizeof(*value->data.list.items));

    if (value->data.list.items == NULL) {
        return false;
    }

    value->data.list.length = length;

    return true;
}

static void destroy_value(Value *value)
{
    if (value == NULL) {
        return;
    }

    if (value->type == VALUE_LIST) {
        for (size_t index = 0U;
             index < value->data.list.length;
             ++index) {
            destroy_value(&value->data.list.items[index]);
        }

        free(value->data.list.items);
        value->data.list.items = NULL;
        value->data.list.length = 0U;
    }
}

static bool values_equal(const Value *left, const Value *right)
{
    if (left == NULL || right == NULL || left->type != right->type) {
        return false;
    }

    if (left->type == VALUE_INTEGER) {
        return left->data.integer == right->data.integer;
    }

    if (left->type != VALUE_LIST ||
        left->data.list.length != right->data.list.length) {
        return false;
    }

    for (size_t index = 0U;
         index < left->data.list.length;
         ++index) {
        if (!values_equal(&left->data.list.items[index],
                          &right->data.list.items[index])) {
            return false;
        }
    }

    return true;
}

static bool nested_list_is_subset(const Value *subset,
                                  const Value *superset)
{
    if (subset == NULL || superset == NULL ||
        subset->type != VALUE_LIST ||
        superset->type != VALUE_LIST) {
        return false;
    }

    if (subset->data.list.length > superset->data.list.length) {
        return false;
    }

    if (subset->data.list.length == 0U) {
        return true;
    }

    if (superset->data.list.length >
        SIZE_MAX / sizeof(bool)) {
        return false;
    }

    bool *matched =
        calloc(superset->data.list.length, sizeof(*matched));

    if (matched == NULL) {
        return false;
    }

    for (size_t subset_index = 0U;
         subset_index < subset->data.list.length;
         ++subset_index) {
        bool found = false;

        for (size_t superset_index = 0U;
             superset_index < superset->data.list.length;
             ++superset_index) {
            if (!matched[superset_index] &&
                values_equal(
                    &subset->data.list.items[subset_index],
                    &superset->data.list.items[superset_index])) {
                matched[superset_index] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            free(matched);
            return false;
        }
    }

    free(matched);

    return true;
}

int main(void)
{
    Value subset;
    Value superset;

    if (!make_list(&subset, 2U)) {
        fputs("Failed to create subset\n", stderr);
        return EXIT_FAILURE;
    }

    if (!make_list(&superset, 3U)) {
        destroy_value(&subset);
        fputs("Failed to create superset\n", stderr);
        return EXIT_FAILURE;
    }

    subset.data.list.items[0] = make_integer(1);

    if (!make_list(&subset.data.list.items[1], 2U)) {
        destroy_value(&subset);
        destroy_value(&superset);
        fputs("Failed to create nested subset\n", stderr);
        return EXIT_FAILURE;
    }

    subset.data.list.items[1].data.list.items[0] = make_integer(2);
    subset.data.list.items[1].data.list.items[1] = make_integer(3);

    superset.data.list.items[0] = make_integer(4);

    if (!make_list(&superset.data.list.items[1], 2U)) {
        destroy_value(&subset);
        destroy_value(&superset);
        fputs("Failed to create nested superset\n", stderr);
        return EXIT_FAILURE;
    }

    superset.data.list.items[1].data.list.items[0] = make_integer(2);
    superset.data.list.items[1].data.list.items[1] = make_integer(3);
    superset.data.list.items[2] = make_integer(1);

    const int result =
        nested_list_is_subset(&subset, &superset)
            ? EXIT_SUCCESS
            : EXIT_FAILURE;

    puts(result == EXIT_SUCCESS ? "true" : "false");

    destroy_value(&subset);
    destroy_value(&superset);

    return result;
}
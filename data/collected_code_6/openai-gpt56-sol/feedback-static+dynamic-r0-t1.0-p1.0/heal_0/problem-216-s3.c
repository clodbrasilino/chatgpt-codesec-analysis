#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_LIST
} ValueType;

typedef struct List List;

typedef struct {
    ValueType type;
    union {
        int integer;
        List *list;
    } data;
} Value;

struct List {
    Value *items;
    size_t length;
};

static void list_destroy(List *list);

static Value value_integer(int number)
{
    Value value;

    value.type = VALUE_INTEGER;
    value.data.integer = number;
    return value;
}

static bool value_list(Value *value, List *list)
{
    if (value == NULL || list == NULL) {
        return false;
    }

    value->type = VALUE_LIST;
    value->data.list = list;
    return true;
}

static List *list_create(size_t length)
{
    List *list = calloc(1, sizeof(*list));

    if (list == NULL) {
        return NULL;
    }

    if (length > 0) {
        if (length > SIZE_MAX / sizeof(*list->items)) {
            free(list);
            return NULL;
        }

        list->items = calloc(length, sizeof(*list->items));
        if (list->items == NULL) {
            free(list);
            return NULL;
        }
    }

    list->length = length;
    return list;
}

static void value_destroy(Value *value)
{
    if (value == NULL) {
        return;
    }

    if (value->type == VALUE_LIST) {
        list_destroy(value->data.list);
        value->data.list = NULL;
    }
}

static void list_destroy(List *list)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0; index < list->length; ++index) {
        value_destroy(&list->items[index]);
    }

    free(list->items);
    free(list);
}

static bool value_equal(const Value *left, const Value *right);

static bool list_equal(const List *left, const List *right)
{
    size_t index;

    if (left == NULL || right == NULL || left->length != right->length) {
        return false;
    }

    for (index = 0; index < left->length; ++index) {
        if (!value_equal(&left->items[index], &right->items[index])) {
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
            return list_equal(left->data.list, right->data.list);
        default:
            return false;
    }
}

static bool nested_list_is_subset(const List *subset, const List *superset)
{
    bool *matched;
    size_t i;
    size_t j;

    if (subset == NULL || superset == NULL) {
        return false;
    }

    if (subset->length > superset->length) {
        return false;
    }

    if (subset->length == 0) {
        return true;
    }

    matched = calloc(superset->length, sizeof(*matched));
    if (matched == NULL) {
        return false;
    }

    for (i = 0; i < subset->length; ++i) {
        bool found = false;

        for (j = 0; j < superset->length; ++j) {
            if (!matched[j] &&
                value_equal(&subset->items[i], &superset->items[j])) {
                matched[j] = true;
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
    List *subset = NULL;
    List *superset = NULL;
    List *subset_nested = NULL;
    List *superset_nested = NULL;
    bool result;
    int status = EXIT_FAILURE;

    subset = list_create(2);
    superset = list_create(3);
    subset_nested = list_create(2);
    superset_nested = list_create(2);

    if (subset == NULL || superset == NULL ||
        subset_nested == NULL || superset_nested == NULL) {
        goto cleanup;
    }

    subset_nested->items[0] = value_integer(2);
    subset_nested->items[1] = value_integer(3);
    superset_nested->items[0] = value_integer(2);
    superset_nested->items[1] = value_integer(3);

    subset->items[0] = value_integer(1);
    if (!value_list(&subset->items[1], subset_nested)) {
        goto cleanup;
    }
    subset_nested = NULL;

    superset->items[0] = value_integer(4);
    if (!value_list(&superset->items[1], superset_nested)) {
        goto cleanup;
    }
    superset_nested = NULL;
    superset->items[2] = value_integer(1);

    result = nested_list_is_subset(subset, superset);
    printf("%s\n", result ? "true" : "false");
    status = result ? EXIT_SUCCESS : EXIT_FAILURE;

cleanup:
    list_destroy(subset_nested);
    list_destroy(superset_nested);
    list_destroy(subset);
    list_destroy(superset);
    return status;
}
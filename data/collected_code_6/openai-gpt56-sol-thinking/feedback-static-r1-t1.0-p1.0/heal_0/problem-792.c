#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_LIST
} ValueType;

typedef struct Value Value;
typedef struct List List;

struct List {
    const Value *items;
    size_t length;
};

struct Value {
    ValueType type;
    union {
        int integer;
        const List *list;
    } data;
};

bool count_lists(const List *list, size_t *count)
{
    size_t total = 0;

    if (list == NULL || count == NULL) {
        return false;
    }

    if (list->length > 0 && list->items == NULL) {
        return false;
    }

    for (size_t i = 0; i < list->length; ++i) {
        switch (list->items[i].type) {
            case VALUE_INTEGER:
                break;
            case VALUE_LIST:
                if (list->items[i].data.list == NULL) {
                    return false;
                }
                ++total;
                break;
            default:
                return false;
        }
    }

    *count = total;
    return true;
}

int main(void)
{
    const List first = { NULL, 0 };
    const List second = { NULL, 0 };
    const List third = { NULL, 0 };

    const Value values[] = {
        { .type = VALUE_LIST, .data.list = &first },
        { .type = VALUE_INTEGER, .data.integer = 42 },
        { .type = VALUE_LIST, .data.list = &second },
        { .type = VALUE_LIST, .data.list = &third }
    };

    const List outer = {
        values,
        sizeof(values) / sizeof(values[0])
    };

    size_t count = 0;

    if (!count_lists(&outer, &count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
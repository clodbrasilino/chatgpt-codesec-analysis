#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TUPLE_INT,
    TUPLE_DOUBLE,
    TUPLE_STRING
} TupleItemType;

typedef struct {
    TupleItemType type;
    union {
        int integer;
        double real;
        const char *string;
    } value;
} TupleItem;

typedef struct {
    const TupleItem *items;
    size_t length;
} Tuple;

int tuple_get(const Tuple *tuple, size_t index, TupleItem *result)
{
    if (tuple == NULL || result == NULL || tuple->items == NULL) {
        return -1;
    }

    if (index >= tuple->length) {
        return -1;
    }

    *result = tuple->items[index];
    return 0;
}

int main(void)
{
    const TupleItem items[] = {
        { .type = TUPLE_INT, .value.integer = 42 },
        { .type = TUPLE_DOUBLE, .value.real = 3.14 },
        { .type = TUPLE_STRING, .value.string = "example" }
    };
    const Tuple tuple = {
        .items = items,
        .length = sizeof(items) / sizeof(items[0])
    };
    TupleItem item;

    if (tuple_get(&tuple, 2U, &item) != 0) {
        fputs("Unable to get tuple item.\n", stderr);
        return EXIT_FAILURE;
    }

    switch (item.type) {
        case TUPLE_INT:
            printf("%d\n", item.value.integer);
            break;
        case TUPLE_DOUBLE:
            printf("%.2f\n", item.value.real);
            break;
        case TUPLE_STRING:
            if (item.value.string == NULL) {
                fputs("Invalid string item.\n", stderr);
                return EXIT_FAILURE;
            }
            printf("%s\n", item.value.string);
            break;
        default:
            fputs("Unknown tuple item type.\n", stderr);
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
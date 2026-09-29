#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ITEM_LONG,
    ITEM_NONE,
    ITEM_STRING
} ItemType;

typedef struct {
    ItemType type;
    union {
        long integer;
        const char *string;
    } value;
} Item;

static int tuple_has_none(const Item *tuple, size_t size, int *has_none)
{
    size_t i;

    if (tuple == NULL || has_none == NULL) {
        return -1;
    }

    *has_none = 0;

    for (i = 0; i < size; ++i) {
        if (tuple[i].type == ITEM_NONE) {
            *has_none = 1;
            break;
        }
    }

    return 0;
}

int main(void)
{
    Item tuple[3] = {
        { .type = ITEM_LONG, .value.integer = 1 },
        { .type = ITEM_NONE, .value.integer = 0 },
        { .type = ITEM_STRING, .value.string = "value" }
    };
    int has_none;

    if (tuple_has_none(tuple, sizeof(tuple) / sizeof(tuple[0]), &has_none) != 0) {
        fprintf(stderr, "Invalid argument\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", has_none ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
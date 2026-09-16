#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int integer_value;
        double double_value;
        char char_value;
        const char *string_value;
    } value;
} TupleElement;

static bool tuple_has_same_type(const TupleElement *tuple, size_t count)
{
    size_t i;

    if (tuple == NULL || count == 0U) {
        return false;
    }

    for (i = 1U; i < count; ++i) {
        if (tuple[i].type != tuple[0].type) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const TupleElement tuple[] = {
        {.type = TYPE_INT, .value.integer_value = 10},
        {.type = TYPE_INT, .value.integer_value = 20},
        {.type = TYPE_INT, .value.integer_value = 30}
    };
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    if (tuple_has_same_type(tuple, count)) {
        (void)printf("All tuple elements have the same data type.\n");
    } else {
        (void)printf("Tuple elements have different data types.\n");
    }

    return 0;
}
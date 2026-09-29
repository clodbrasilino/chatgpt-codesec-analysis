#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    TYPE_INT
} DataType;

typedef struct {
    DataType type;
    int value;
} TupleElement;

static bool tuple_has_same_type(const TupleElement *tuple, size_t count)
{
    if (tuple == NULL || count == 0U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (tuple[i].type != tuple[0].type) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const TupleElement tuple[] = {
        {TYPE_INT, 10},
        {TYPE_INT, 20},
        {TYPE_INT, 30}
    };
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    const char *message = tuple_has_same_type(tuple, count)
        ? "All elements have the same data type.\n"
        : "Elements have different data types.\n";

    return printf("%s", message) < 0 ? 1 : 0;
}
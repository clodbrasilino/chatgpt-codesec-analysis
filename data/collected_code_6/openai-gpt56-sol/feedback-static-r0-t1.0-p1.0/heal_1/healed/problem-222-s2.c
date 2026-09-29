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
} TupleElement;

static bool all_same_type(const TupleElement *tuple, size_t count)
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
        {TYPE_INT},
        {TYPE_INT},
        {TYPE_INT}
    };
    const size_t count = sizeof tuple / sizeof tuple[0];

    const char *message = all_same_type(tuple, count)
        ? "All tuple elements have the same data type.\n"
        : "Tuple elements have different data types.\n";

    return fputs(message, stdout) == EOF ? 1 : 0;
}
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
    const void *value;
} TupleElement;

static bool all_same_type(const TupleElement *tuple, size_t count)
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
    int first = 10;
    int second = 20;
    int third = 30;
    TupleElement tuple[] = {
        {TYPE_INT, &first},
        {TYPE_INT, &second},
        {TYPE_INT, &third}
    };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);

    if (all_same_type(tuple, count)) {
        if (printf("All tuple elements have the same data type.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Tuple elements have different data types.\n") < 0) {
            return 1;
        }
    }

    return 0;
}
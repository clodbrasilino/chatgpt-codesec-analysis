#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    TYPE_INT
} DataType;

typedef struct {
    DataType type;
    /* Possible weaknesses found:
     *  struct member 'TupleElement::integer_value' is never used. [unusedStructMember]
     */
    int integer_value;
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
        {TYPE_INT, 10},
        {TYPE_INT, 20},
        {TYPE_INT, 30}
    };
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    if (tuple_has_same_type(tuple, count)) {
        (void)printf("All tuple elements have the same data type.\n");
    } else {
        (void)printf("Tuple elements have different data types.\n");
    }

    return 0;
}
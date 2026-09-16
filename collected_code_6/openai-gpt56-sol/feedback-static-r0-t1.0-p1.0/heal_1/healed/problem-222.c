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
    const TupleElement int_tuple[] = {
        {.type = TYPE_INT, .value.integer_value = 10},
        {.type = TYPE_INT, .value.integer_value = 20},
        {.type = TYPE_INT, .value.integer_value = 30}
    };
    const TupleElement double_tuple[] = {
        {.type = TYPE_DOUBLE, .value.double_value = 1.5},
        {.type = TYPE_DOUBLE, .value.double_value = 2.5}
    };
    const TupleElement char_tuple[] = {
        {.type = TYPE_CHAR, .value.char_value = 'A'},
        {.type = TYPE_CHAR, .value.char_value = 'B'}
    };
    const TupleElement string_tuple[] = {
        {.type = TYPE_STRING, .value.string_value = "first"},
        {.type = TYPE_STRING, .value.string_value = "second"}
    };

    const bool all_valid =
        tuple_has_same_type(int_tuple, sizeof(int_tuple) / sizeof(int_tuple[0])) &&
        tuple_has_same_type(double_tuple, sizeof(double_tuple) / sizeof(double_tuple[0])) &&
        tuple_has_same_type(char_tuple, sizeof(char_tuple) / sizeof(char_tuple[0])) &&
        tuple_has_same_type(string_tuple, sizeof(string_tuple) / sizeof(string_tuple[0]));

    if (all_valid) {
        (void)printf("All tuple elements have the same data type.\n");
    } else {
        (void)printf("Tuple elements have different data types.\n");
    }

    return 0;
}
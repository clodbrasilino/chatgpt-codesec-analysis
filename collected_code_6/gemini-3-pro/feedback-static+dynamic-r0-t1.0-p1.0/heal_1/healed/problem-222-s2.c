#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        char char_val;
        char* string_val;
    } value;
} TupleElement;

bool are_all_elements_same_type(const TupleElement* tuple, size_t size);

bool are_all_elements_same_type(const TupleElement* tuple, size_t size) {
    if (tuple == NULL) {
        return false;
    }
    
    if (size <= 1) {
        return true;
    }

    DataType first_type = tuple[0].type;

    for (size_t i = 1; i < size; ++i) {
        if (tuple[i].type != first_type) {
            return false;
        }
    }

    return true;
}

int main(void) {
    TupleElement tuple1[] = {
        {TYPE_INT, .value.int_val = 10},
        {TYPE_INT, .value.int_val = 20},
        {TYPE_INT, .value.int_val = 30}
    };
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);

    TupleElement tuple2[] = {
        {TYPE_INT, .value.int_val = 10},
        {TYPE_FLOAT, .value.float_val = 20.5f},
        {TYPE_INT, .value.int_val = 30}
    };
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    TupleElement tuple3[] = {
        {TYPE_CHAR, .value.char_val = 'a'},
        {TYPE_CHAR, .value.char_val = 'b'}
    };
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    TupleElement tuple4[] = {
        {TYPE_STRING, .value.string_val = "foo"},
        {TYPE_STRING, .value.string_val = "bar"}
    };
    size_t size4 = sizeof(tuple4) / sizeof(tuple4[0]);

    bool result1 = are_all_elements_same_type(tuple1, size1);
    bool result2 = are_all_elements_same_type(tuple2, size2);
    bool result3 = are_all_elements_same_type(tuple3, size3);
    bool result4 = are_all_elements_same_type(tuple4, size4);

    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
    printf("%d\n", result4);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        double double_val;
        char char_val;
        char *str_val;
    } value;
} TupleElement;

bool all_same_type(const TupleElement elements[], size_t size) {
    if (size == 0 || elements == NULL) {
        return false;
    }
    
    DataType first_type = elements[0].type;
    
    if (first_type == TYPE_UNKNOWN) {
        return false;
    }
    
    for (size_t i = 1; i < size; i++) {
        if (elements[i].type != first_type) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    TupleElement tuple1[] = {
        {TYPE_INT, {.int_val = 1}},
        {TYPE_INT, {.int_val = 2}},
        {TYPE_INT, {.int_val = 3}}
    };
    
    TupleElement tuple2[] = {
        {TYPE_FLOAT, {.float_val = 1.5f}},
        {TYPE_INT, {.int_val = 2}},
        {TYPE_DOUBLE, {.double_val = 3.14}}
    };
    
    TupleElement tuple3[] = {
        {TYPE_STRING, {.str_val = "hello"}},
        {TYPE_STRING, {.str_val = "world"}},
        {TYPE_STRING, {.str_val = "test"}}
    };
    
    TupleElement tuple4[] = {
        {TYPE_CHAR, {.char_val = 'a'}},
        {TYPE_CHAR, {.char_val = 'b'}},
        {TYPE_CHAR, {.char_val = 'c'}}
    };
    
    printf("Tuple 1 (all int): %s\n", all_same_type(tuple1, 3) ? "true" : "false");
    printf("Tuple 2 (mixed): %s\n", all_same_type(tuple2, 3) ? "true" : "false");
    printf("Tuple 3 (all string): %s\n", all_same_type(tuple3, 3) ? "true" : "false");
    printf("Tuple 4 (all char): %s\n", all_same_type(tuple4, 3) ? "true" : "false");
    
    TupleElement *empty = NULL;
    bool result = all_same_type(empty, 0);
    printf("Empty tuple: %s\n", result ? "true" : "false");
    
    return 0;
}
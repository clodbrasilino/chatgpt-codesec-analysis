#include <stdio.h>
#include <string.h>
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

bool all_same_type(TupleElement elements[], size_t size) {
    if (size == 0) {
        return true;
    }
    
    DataType first_type = elements[0].type;
    if (first_type == TYPE_UNKNOWN) {
        return false;
    }
    
    for (size_t i = 1; i < size; i++) {
        if (elements[i].type != first_type || elements[i].type == TYPE_UNKNOWN) {
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
    
    TupleElement empty_tuple[] = {};
    
    printf("Tuple 1 (all int): %s\n", all_same_type(tuple1, 3) ? "true" : "false");
    printf("Tuple 2 (mixed): %s\n", all_same_type(tuple2, 3) ? "true" : "false");
    printf("Tuple 3 (all string): %s\n", all_same_type(tuple3, 3) ? "true" : "false");
    printf("Empty tuple: %s\n", all_same_type(empty_tuple, 0) ? "true" : "false");
    
    return 0;
}
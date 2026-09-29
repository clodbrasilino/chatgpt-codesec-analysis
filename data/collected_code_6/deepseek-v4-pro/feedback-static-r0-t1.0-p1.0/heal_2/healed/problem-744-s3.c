#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_POINTER
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_val;
        float float_val;
        double double_val;
        char char_val;
        char *str_val;
        void *ptr_val;
    } value;
    bool is_none;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

Tuple create_tuple(TupleElement *elements, size_t count) {
    Tuple tuple;
    tuple.elements = elements;
    tuple.count = count;
    return tuple;
}

bool has_none_value(Tuple tuple) {
    if (tuple.elements == NULL && tuple.count > 0) {
        return true;
    }
    
    if (tuple.elements == NULL && tuple.count == 0) {
        return false;
    }
    
    for (size_t i = 0; i < tuple.count; i++) {
        if (tuple.elements[i].is_none) {
            return true;
        }
    }
    return false;
}

int main(void) {
    TupleElement elements[4] = {
        {TYPE_INT, {.int_val = 42}, false},
        {TYPE_STRING, {.str_val = "hello"}, false},
        {TYPE_POINTER, {.ptr_val = NULL}, true},
        {TYPE_FLOAT, {.float_val = 3.14f}, false}
    };
    
    Tuple tuple = create_tuple(elements, 4);
    
    if (has_none_value(tuple)) {
        printf("Tuple contains at least one none value\n");
    } else {
        printf("Tuple does not contain any none value\n");
    }
    
    TupleElement elements_no_none[3] = {
        {TYPE_INT, {.int_val = 10}, false},
        {TYPE_DOUBLE, {.double_val = 2.718}, false},
        {TYPE_CHAR, {.char_val = 'A'}, false}
    };
    
    Tuple tuple_no_none = create_tuple(elements_no_none, 3);
    
    if (has_none_value(tuple_no_none)) {
        printf("Tuple contains at least one none value\n");
    } else {
        printf("Tuple does not contain any none value\n");
    }
    
    Tuple empty_tuple = create_tuple(NULL, 0);
    
    if (has_none_value(empty_tuple)) {
        printf("Tuple contains at least one none value\n");
    } else {
        printf("Tuple does not contain any none value\n");
    }
    
    return 0;
}
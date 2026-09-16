#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
    TYPE_NONE,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_PTR
} TupleType;

typedef struct {
    TupleType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
        void *ptr_val;
    } value;
} TupleElement;

bool has_none_value(int count, ...) {
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; i++) {
        TupleElement elem = va_arg(args, TupleElement);
        if (elem.type == TYPE_NONE) {
            va_end(args);
            return true;
        }
    }
    
    va_end(args);
    return false;
}

int main(void) {
    TupleElement tuple1[] = {
        {TYPE_INT, {.int_val = 42}},
        {TYPE_STRING, {.str_val = "hello"}},
        {TYPE_NONE, {.ptr_val = NULL}}
    };
    
    TupleElement tuple2[] = {
        {TYPE_INT, {.int_val = 10}},
        {TYPE_FLOAT, {.float_val = 3.14f}},
        {TYPE_STRING, {.str_val = "world"}}
    };
    
    printf("Tuple 1 has none: %s\n", 
           has_none_value(3, tuple1[0], tuple1[1], tuple1[2]) ? "true" : "false");
    
    printf("Tuple 2 has none: %s\n", 
           has_none_value(3, tuple2[0], tuple2[1], tuple2[2]) ? "true" : "false");
    
    return 0;
}
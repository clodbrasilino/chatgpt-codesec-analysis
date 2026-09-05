#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        double d;
        char c;
        char *s;
    /* Possible weaknesses found:
     *  struct member 'TupleElement::value' is never used. [unusedStructMember]
     */
    } value;
} TupleElement;

bool check_same_type(TupleElement *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return false;
    }
    
    if (size == 1) {
        return true;
    }
    
    DataType first_type = tuple[0].type;
    
    for (size_t i = 1; i < size; i++) {
        if (tuple[i].type != first_type) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    TupleElement tuple1[] = {
        {TYPE_INT, {.i = 10}},
        {TYPE_INT, {.i = 20}},
        {TYPE_INT, {.i = 30}}
    };
    
    TupleElement tuple2[] = {
        {TYPE_INT, {.i = 10}},
        {TYPE_FLOAT, {.f = 20.5f}},
        {TYPE_INT, {.i = 30}}
    };
    
    TupleElement tuple3[] = {
        {TYPE_STRING, {.s = "hello"}},
        {TYPE_STRING, {.s = "world"}},
        {TYPE_STRING, {.s = "test"}}
    };
    
    TupleElement tuple4[] = {
        {TYPE_DOUBLE, {.d = 3.14159}},
        {TYPE_DOUBLE, {.d = 2.71828}},
        {TYPE_DOUBLE, {.d = 1.41421}}
    };
    
    TupleElement tuple5[] = {
        {TYPE_CHAR, {.c = 'a'}},
        {TYPE_CHAR, {.c = 'b'}},
        {TYPE_CHAR, {.c = 'c'}}
    };
    
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    size_t size4 = sizeof(tuple4) / sizeof(tuple4[0]);
    size_t size5 = sizeof(tuple5) / sizeof(tuple5[0]);
    
    if (check_same_type(tuple1, size1)) {
        printf("Tuple1: All elements have the same type\n");
    } else {
        printf("Tuple1: Elements have different types\n");
    }
    
    if (check_same_type(tuple2, size2)) {
        printf("Tuple2: All elements have the same type\n");
    } else {
        printf("Tuple2: Elements have different types\n");
    }
    
    if (check_same_type(tuple3, size3)) {
        printf("Tuple3: All elements have the same type\n");
    } else {
        printf("Tuple3: Elements have different types\n");
    }
    
    if (check_same_type(tuple4, size4)) {
        printf("Tuple4: All elements have the same type\n");
    } else {
        printf("Tuple4: Elements have different types\n");
    }
    
    if (check_same_type(tuple5, size5)) {
        printf("Tuple5: All elements have the same type\n");
    } else {
        printf("Tuple5: Elements have different types\n");
    }
    
    return 0;
}
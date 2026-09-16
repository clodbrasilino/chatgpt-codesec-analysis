#include <stdio.h>
#include <string.h>

typedef union {
    int int_val;
    float float_val;
    double double_val;
    /* Possible weaknesses found:
     *  union member 'TupleValue::char_val' is never used. [unusedStructMember]
     */
    char char_val;
    /* Possible weaknesses found:
     *  union member 'TupleValue::str_val' is never used. [unusedStructMember]
     */
    char *str_val;
    /* Possible weaknesses found:
     *  union member 'TupleValue::ptr_val' is never used. [unusedStructMember]
     */
    void *ptr_val;
} TupleValue;

typedef struct {
    int type;
    TupleValue value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    int size;
} Tuple;

int check_same_type(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0) {
        return 0;
    }
    
    int first_type = tuple->elements[0].type;
    
    for (int i = 1; i < tuple->size; i++) {
        if (tuple->elements[i].type != first_type) {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    TupleElement elements1[] = {
        {1, .value.int_val = 10},
        {1, .value.int_val = 20},
        {1, .value.int_val = 30}
    };
    Tuple tuple1 = {elements1, 3};
    
    TupleElement elements2[] = {
        {1, .value.int_val = 10},
        {2, .value.float_val = 20.5f},
        {1, .value.int_val = 30}
    };
    Tuple tuple2 = {elements2, 3};
    
    TupleElement elements3[] = {
        {3, .value.double_val = 1.5},
        {3, .value.double_val = 2.5}
    };
    Tuple tuple3 = {elements3, 2};
    
    printf("Tuple 1 same type: %s\n", check_same_type(&tuple1) ? "Yes" : "No");
    printf("Tuple 2 same type: %s\n", check_same_type(&tuple2) ? "Yes" : "No");
    printf("Tuple 3 same type: %s\n", check_same_type(&tuple3) ? "Yes" : "No");
    
    Tuple empty_tuple = {NULL, 0};
    printf("Empty tuple same type: %s\n", check_same_type(&empty_tuple) ? "Yes" : "No");
    
    return 0;
}
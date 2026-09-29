#include <stdio.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_NONE
} ValueType;

typedef struct {
    ValueType type;
    /* Possible weaknesses found:
     *  struct member 'TupleElement::value' is never used. [unusedStructMember]
     */
    int value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

bool has_none(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type == TYPE_NONE) {
            return true;
        }
    }
    return false;
}

int main(void) {
    TupleElement elements1[] = {
        {TYPE_INT, 1},
        {TYPE_NONE, 0},
        {TYPE_INT, 3}
    };
    Tuple tuple1 = {elements1, 3};
    
    TupleElement elements2[] = {
        {TYPE_INT, 1},
        {TYPE_INT, 2},
        {TYPE_INT, 3}
    };
    Tuple tuple2 = {elements2, 3};
    
    printf("Tuple 1 has none: %s\n", has_none(&tuple1) ? "true" : "false");
    printf("Tuple 2 has none: %s\n", has_none(&tuple2) ? "true" : "false");
    
    return 0;
}
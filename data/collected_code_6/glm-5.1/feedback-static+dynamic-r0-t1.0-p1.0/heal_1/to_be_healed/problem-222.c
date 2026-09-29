#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_DOUBLE,
    TYPE_PTR
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::char_val' is never used. [unusedStructMember]
         */
        char char_val;
        double double_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::ptr_val' is never used. [unusedStructMember]
         */
        void *ptr_val;
    } value;
} TupleElement;

typedef struct {
    TupleElement *items;
    size_t count;
} Tuple;

bool check_tuple_types(const Tuple *t) {
    if (t == NULL || t->items == NULL) {
        return false;
    }
    if (t->count == 0) {
        return true;
    }
    DataType first_type = t->items[0].type;
    for (size_t i = 1; i < t->count; i++) {
        if (t->items[i].type != first_type) {
            return false;
        }
    }
    return true;
}

int main(void) {
    TupleElement items1[3] = {
        {.type = TYPE_INT, .value.int_val = 1},
        {.type = TYPE_INT, .value.int_val = 2},
        {.type = TYPE_INT, .value.int_val = 3}
    };
    Tuple t1 = {.items = items1, .count = 3};

    TupleElement items2[3] = {
        {.type = TYPE_INT, .value.int_val = 1},
        {.type = TYPE_FLOAT, .value.float_val = 2.5f},
        {.type = TYPE_DOUBLE, .value.double_val = 3.5}
    };
    Tuple t2 = {.items = items2, .count = 3};

    Tuple t3 = {.items = NULL, .count = 0};

    bool res1 = check_tuple_types(&t1);
    bool res2 = check_tuple_types(&t2);
    bool res3 = check_tuple_types(&t3);

    printf("Tuple 1 same type: %s\n", res1 ? "True" : "False");
    printf("Tuple 2 same type: %s\n", res2 ? "True" : "False");
    printf("Tuple 3 same type: %s\n", res3 ? "True" : "False");

    return 0;
}
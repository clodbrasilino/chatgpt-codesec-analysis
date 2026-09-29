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
        char char_val;
        double double_val;
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

    TupleElement items3[2] = {
        {.type = TYPE_CHAR, .value.char_val = 'a'},
        {.type = TYPE_CHAR, .value.char_val = 'b'}
    };
    Tuple t3 = {.items = items3, .count = 2};

    TupleElement items4[2] = {
        {.type = TYPE_PTR, .value.ptr_val = NULL},
        {.type = TYPE_PTR, .value.ptr_val = NULL}
    };
    Tuple t4 = {.items = items4, .count = 2};

    Tuple t5 = {.items = NULL, .count = 0};

    bool res1 = check_tuple_types(&t1);
    bool res2 = check_tuple_types(&t2);
    bool res3 = check_tuple_types(&t3);
    bool res4 = check_tuple_types(&t4);
    bool res5 = check_tuple_types(&t5);

    printf("Tuple 1 same type: %s\n", res1 ? "True" : "False");
    printf("Tuple 2 same type: %s\n", res2 ? "True" : "False");
    printf("Tuple 3 same type: %s\n", res3 ? "True" : "False");
    printf("Tuple 4 same type: %s\n", res4 ? "True" : "False");
    printf("Tuple 5 same type: %s\n", res5 ? "True" : "False");

    return 0;
}
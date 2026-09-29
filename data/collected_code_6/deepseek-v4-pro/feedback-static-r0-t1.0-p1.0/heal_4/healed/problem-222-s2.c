#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

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
        int i;
        float f;
        double d;
        char c;
        char *s;
    } value;
} TupleElement;

bool all_same_type(const TupleElement *elements, size_t count) {
    if (elements == NULL || count == 0) {
        return false;
    }

    DataType first_type = elements[0].type;
    if (first_type == TYPE_UNKNOWN) {
        return false;
    }

    for (size_t i = 1; i < count; i++) {
        if (elements[i].type != first_type) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const TupleElement tuple1[] = {
        {TYPE_INT, {.i = 10}},
        {TYPE_INT, {.i = 20}},
        {TYPE_INT, {.i = 30}}
    };

    const TupleElement tuple2[] = {
        {TYPE_INT, {.i = 10}},
        {TYPE_FLOAT, {.f = 20.5f}},
        {TYPE_INT, {.i = 30}}
    };

    const TupleElement tuple3[] = {
        {TYPE_DOUBLE, {.d = 1.5}},
        {TYPE_DOUBLE, {.d = 2.5}}
    };

    const TupleElement tuple4[] = {
        {TYPE_CHAR, {.c = 'a'}},
        {TYPE_CHAR, {.c = 'b'}},
        {TYPE_CHAR, {.c = 'c'}},
        {TYPE_CHAR, {.c = 'd'}}
    };

    const TupleElement tuple5[] = {
        {TYPE_STRING, {.s = "hello"}},
        {TYPE_STRING, {.s = "world"}}
    };

    printf("tuple1 all same type: %s\n", all_same_type(tuple1, 3) ? "true" : "false");
    printf("tuple2 all same type: %s\n", all_same_type(tuple2, 3) ? "true" : "false");
    printf("tuple3 all same type: %s\n", all_same_type(tuple3, 2) ? "true" : "false");
    printf("tuple4 all same type: %s\n", all_same_type(tuple4, 4) ? "true" : "false");
    printf("tuple5 all same type: %s\n", all_same_type(tuple5, 2) ? "true" : "false");
    printf("empty tuple all same type: %s\n", all_same_type(NULL, 0) ? "true" : "false");
    printf("NULL tuple all same type: %s\n", all_same_type(NULL, 5) ? "true" : "false");

    return 0;
}
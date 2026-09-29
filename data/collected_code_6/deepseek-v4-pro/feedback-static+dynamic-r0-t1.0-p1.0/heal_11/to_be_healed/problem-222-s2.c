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
        const char *s;
    /* Possible weaknesses found:
     *  struct member 'TupleElement::value' is never used. [unusedStructMember]
     */
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
        /* Possible weaknesses found:
         *  Condition 'elements[i].type==TYPE_UNKNOWN' is always false [knownConditionTrueFalse]
         */
        if (elements[i].type == TYPE_UNKNOWN) {
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

    const TupleElement tuple6[] = {
        {TYPE_INT, {.i = 1}},
        {TYPE_UNKNOWN, {.i = 0}},
        {TYPE_INT, {.i = 3}}
    };

    const TupleElement tuple7[] = {
        {TYPE_UNKNOWN, {.i = 1}},
        {TYPE_UNKNOWN, {.i = 2}}
    };

    bool result1 = all_same_type(tuple1, 3);
    bool result2 = all_same_type(tuple2, 3);
    bool result3 = all_same_type(tuple3, 2);
    bool result4 = all_same_type(tuple4, 4);
    bool result5 = all_same_type(tuple5, 2);
    bool result6 = all_same_type(tuple6, 3);
    bool result7 = all_same_type(tuple7, 2);
    /* Possible weaknesses found:
     *  Assignment 'result8=all_same_type(NULL,0)', assigned value is 0
     *  Calling function 'all_same_type' returns 0
     */
    bool result8 = all_same_type(NULL, 0);
    bool result9 = all_same_type(tuple1, 0);

    printf("tuple1 all same type: %s\n", result1 ? "true" : "false");
    printf("tuple2 all same type: %s\n", result2 ? "true" : "false");
    printf("tuple3 all same type: %s\n", result3 ? "true" : "false");
    printf("tuple4 all same type: %s\n", result4 ? "true" : "false");
    printf("tuple5 all same type: %s\n", result5 ? "true" : "false");
    printf("tuple6 all same type: %s\n", result6 ? "true" : "false");
    printf("tuple7 all same type: %s\n", result7 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'result8' is always false
     *  Condition 'result8' is always false [knownConditionTrueFalse]
     */
    printf("NULL elements all same type: %s\n", result8 ? "true" : "false");
    printf("zero count all same type: %s\n", result9 ? "true" : "false");

    return 0;
}
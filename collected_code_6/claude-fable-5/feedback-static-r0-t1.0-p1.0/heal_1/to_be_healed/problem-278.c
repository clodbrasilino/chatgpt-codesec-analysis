#include <stdio.h>
#include <stddef.h>

typedef enum {
    ELEM_INT,
    ELEM_RECORD
} ElemType;

typedef struct {
    ElemType type;
    /* Possible weaknesses found:
     *  struct member 'Element::value' is never used. [unusedStructMember]
     */
    int value;
} Element;

size_t count_before_record(const Element *tuple, size_t length)
{
    size_t count = 0U;

    if (tuple == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < length; i++) {
        if (tuple[i].type == ELEM_RECORD) {
            break;
        }
        count++;
    }

    return count;
}

int main(void)
{
    Element tuple1[] = {
        { ELEM_INT, 1 },
        { ELEM_INT, 5 },
        { ELEM_INT, 7 },
        { ELEM_RECORD, 0 },
        { ELEM_INT, 9 }
    };

    Element tuple2[] = {
        { ELEM_INT, 2 },
        { ELEM_INT, 9 },
        { ELEM_RECORD, 0 },
        { ELEM_INT, 11 }
    };

    Element tuple3[] = {
        { ELEM_INT, 11 },
        { ELEM_INT, 14 },
        { ELEM_INT, 5 },
        { ELEM_INT, 9 },
        { ELEM_RECORD, 0 }
    };

    size_t result1 = count_before_record(tuple1, sizeof(tuple1) / sizeof(tuple1[0]));
    size_t result2 = count_before_record(tuple2, sizeof(tuple2) / sizeof(tuple2[0]));
    size_t result3 = count_before_record(tuple3, sizeof(tuple3) / sizeof(tuple3[0]));

    if (printf("Count before record in tuple1: %zu\n", result1) < 0) {
        return 1;
    }
    if (printf("Count before record in tuple2: %zu\n", result2) < 0) {
        return 1;
    }
    if (printf("Count before record in tuple3: %zu\n", result3) < 0) {
        return 1;
    }

    return 0;
}
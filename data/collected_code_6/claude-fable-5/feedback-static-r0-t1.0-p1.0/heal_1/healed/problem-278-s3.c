#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEM_INT,
    ELEM_TUPLE
} ElemType;

typedef struct {
    ElemType type;
} Element;

int count_before_record(const Element *elements, size_t length, size_t *count)
{
    size_t i;

    if (elements == NULL || count == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (elements[i].type == ELEM_TUPLE) {
            *count = i;
            return 0;
        }
    }

    return -1;
}

int main(void)
{
    Element tuple1[] = {
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_TUPLE },
        { ELEM_INT }
    };
    Element tuple2[] = {
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_TUPLE },
        { ELEM_INT },
        { ELEM_INT }
    };
    Element tuple3[] = {
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_INT },
        { ELEM_TUPLE },
        { ELEM_INT }
    };
    size_t count = 0;

    if (count_before_record(tuple1, sizeof(tuple1) / sizeof(tuple1[0]), &count) == 0) {
        printf("Elements before record: %zu\n", count);
    } else {
        printf("No record found in tuple1\n");
    }

    if (count_before_record(tuple2, sizeof(tuple2) / sizeof(tuple2[0]), &count) == 0) {
        printf("Elements before record: %zu\n", count);
    } else {
        printf("No record found in tuple2\n");
    }

    if (count_before_record(tuple3, sizeof(tuple3) / sizeof(tuple3[0]), &count) == 0) {
        printf("Elements before record: %zu\n", count);
    } else {
        printf("No record found in tuple3\n");
    }

    return EXIT_SUCCESS;
}
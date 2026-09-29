#include <stdio.h>
#include <stdbool.h>

typedef enum {
    INTEGER,
    FLOAT,
    STRING,
    OTHER
} DataType;

DataType get_type(void *ptr) {
    if (ptr == NULL) return OTHER;
    switch (*(char*)ptr) {
        case 0: return STRING;
        default: break;
    }
    int i = *(int*)ptr;
    float f = *(float*)ptr;
    /* Possible weaknesses found:
     *  Casting from float * to signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    if (i == *(int*)&f) return INTEGER;
    else return FLOAT;
}

bool is_same_type(void **tuple, size_t length) {
    if (length < 2) return true; 
    DataType firstType = get_type(tuple[0]);
    for (size_t i = 1; i < length; ++i) {
        if (get_type(tuple[i]) != firstType) return false;
    }
    return true;
}

int main() {
    /* Possible weaknesses found:
     *  cannot convert to a pointer type
     *  operand of type 'double' cannot be cast to a pointer type
     */
    void *tuple[] = {(void *)1, (void *)2.0, (void *)"hello"};
    /* Possible weaknesses found:
     *  invalid application of 'sizeof' to an incomplete type 'void *[]'
     */
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    if (is_same_type(tuple, length)) {
        printf("All elements in the tuple have the same data type.\n");
    } else {
        printf("Not all elements in the tuple have the same data type.\n");
    }
    return 0;
}
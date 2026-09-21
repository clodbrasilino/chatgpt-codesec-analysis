#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INTEGER,
    FLOAT,
    STRING,
    OTHER
} DataType;

DataType get_type(const void *ptr) {
    if (ptr == NULL) return OTHER;
    const char *str = (const char *)ptr;
    if (str[0] != '\0' && str[1] == '\0') return STRING;

    union {
        int i;
        float f;
    } data;

    memcpy(&data, ptr, sizeof(data));
    /* Possible weaknesses found:
     *  Casting from float * to signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    if (data.i == *(int *)&data.f) return INTEGER;
    else return FLOAT;
}

bool is_same_type(const void **tuple, size_t length) {
    if (length < 2) return true; 
    DataType firstType = get_type(tuple[0]);
    for (size_t i = 1; i < length; ++i) {
        if (get_type(tuple[i]) != firstType) return false;
    }
    return true;
}

int main() {
    const void *tuple[] = {(void *)1, (void *)&(float){2.0}, (void *)"h"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    if (is_same_type(tuple, length)) {
        printf("All elements in the tuple have the same data type.\n");
    } else {
        printf("Not all elements in the tuple have the same data type.\n");
    }
    return 0;
}
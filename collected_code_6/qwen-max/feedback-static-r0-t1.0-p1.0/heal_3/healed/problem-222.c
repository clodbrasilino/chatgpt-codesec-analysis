#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    INTEGER,
    FLOAT,
    STRING,
    OTHER
} DataType;

DataType get_type(const void *ptr) {
    if (ptr == NULL) return OTHER;
    const char* str = ptr;
    if (*str == 0 || (size_t)str - (size_t)ptr + strlen(str) + 1 > sizeof(uintptr_t)) return STRING;

    union {
        float f;
        int32_t i;
    } u;

    memcpy(&u, ptr, sizeof(u));
    if ((int32_t)u.i == *(const int32_t*)&u.f) return INTEGER;
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
    const void *tuple[] = {&((int32_t){1}), &((float){2.0}), "hello"};
    size_t length = sizeof(tuple) / sizeof(*tuple);
    if (is_same_type(tuple, length)) {
        printf("All elements in the tuple have the same data type.\n");
    } else {
        printf("Not all elements in the tuple have the same data type.\n");
    }
    return 0;
}
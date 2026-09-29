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

DataType get_type(void *ptr) {
    if (ptr == NULL) return OTHER;
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as pointer to const [constVariablePointer]
     */
    char *str = (char *)ptr;
    if (str[0] != '\0' && str[1] == '\0') return STRING;
    int i;
    float f;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&i, ptr, sizeof(int));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&f, ptr, sizeof(float));
    /* Possible weaknesses found:
     *  Variable 'p' can be declared as pointer to const [constVariablePointer]
     *  Casting from float * to signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    int *p = (int *)&f;
    if (i == *p) return INTEGER;
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
    void *tuple[] = {(void *)1, (void *)&(float){2.0}, (void *)"hello"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    if (is_same_type(tuple, length)) {
        printf("All elements in the tuple have the same data type.\n");
    } else {
        printf("Not all elements in the tuple have the same data type.\n");
    }
    return 0;
}
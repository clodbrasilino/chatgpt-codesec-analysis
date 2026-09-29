#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memcpy'
  */

typedef enum {
    INTEGER,
    FLOAT,
    STRING,
    OTHER
} DataType;

DataType get_type(const void *ptr) {
    if (ptr == NULL) return OTHER;
    if (*(const char*)ptr == 0) return STRING;

    union {
        float f;
        int32_t i;
    } u;

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
     *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    memcpy(&u, ptr, sizeof(u));

    /* Possible weaknesses found:
     *  Casting from float * to const signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    if (u.i == *(const int32_t*)&u.f) return INTEGER;
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
    /* Possible weaknesses found:
     *  cannot convert to a pointer type
     *  operand of type 'double' cannot be cast to a pointer type
     */
    const void *tuple[] = {(const void *)1, (const void *)2.0, (const void *)"hello"};
    /* Possible weaknesses found:
     *  invalid application of 'sizeof' to an incomplete type 'const void *[]'
     */
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    if (is_same_type(tuple, length)) {
        printf("All elements in the tuple have the same data type.\n");
    } else {
        printf("Not all elements in the tuple have the same data type.\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT,
    FLOAT,
    STRING,
    UNKNOWN
} DataType;

DataType get_type(void *value) {
    if (strcmp((char *)value, "int") == 0) return INT;
    if (strcmp((char *)value, "float") == 0) return FLOAT;
    if (strcmp((char *)value, "string") == 0) return STRING;
    return UNKNOWN;
}

int all_elements_same_type(void **tuple, int size) {
    if (size == 0) return 1;
    
    DataType first_type = get_type(tuple[0]);
    
    for (int i = 1; i < size; i++) {
        if (get_type(tuple[i]) != first_type) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    void *tuple[] = {(void*)"int", (void*)"int", (void*)"int"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    if (all_elements_same_type(tuple, size)) {
        printf("All elements have the same type.\n");
    } else {
        printf("Elements do not have the same type.\n");
    }
    
    return 0;
}
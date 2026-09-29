#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple convert_string_to_tuple(const char *tuple_str) {
    IntTuple tuple = {NULL, 0};
    if (!tuple_str) {
        return tuple;
    }

    const char *start = strchr(tuple_str, '(');
    const char *end = strrchr(tuple_str, ')');

    if (!start || !end || start >= end) {
        return tuple;
    }

    size_t length = (size_t)(end - start - 1);
    char *inner_str = (char *)malloc(length + 1);
    if (!inner_str) {
        return tuple;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(inner_str, start + 1, length);
    inner_str[length] = '\0';

    size_t count = 0;
    if (length > 0) {
        count = 1;
        for (size_t i = 0; i < length; ++i) {
            if (inner_str[i] == ',') {
                count++;
            }
        }
    }

    if (count == 0) {
        free(inner_str);
        return tuple;
    }

    tuple.elements = (int *)malloc(count * sizeof(int));
    if (!tuple.elements) {
        free(inner_str);
        return tuple;
    }

    char *token = strtok(inner_str, ",");
    size_t index = 0;
    while (token && index < count) {
        tuple.elements[index++] = (int)strtol(token, NULL, 10);
        token = strtok(NULL, ",");
    }

    tuple.size = index;

    free(inner_str);
    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple && tuple->elements) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char *str = "(10, -5, 42, 0, 100)";
    
    IntTuple tuple = convert_string_to_tuple(str);
    
    if (tuple.elements) {
        for (size_t i = 0; i < tuple.size; ++i) {
            printf("%d ", tuple.elements[i]);
        }
        printf("\n");
        free_tuple(&tuple);
    } else {
        printf("Failed to parse tuple.\n");
    }
    
    return 0;
}
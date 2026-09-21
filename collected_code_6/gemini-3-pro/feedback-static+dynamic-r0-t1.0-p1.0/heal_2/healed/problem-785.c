#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* elements;
    size_t size;
} IntTuple;

IntTuple convertStringToIntTuple(const char* tupleString, size_t max_len) {
    IntTuple tuple = {NULL, 0};
    
    if (tupleString == NULL) {
        return tuple;
    }

    size_t len = strnlen(tupleString, max_len);
    if (len < 2 || len == max_len || tupleString[0] != '(' || tupleString[len - 1] != ')') {
        return tuple;
    }

    char* strCopy = (char*)malloc(len - 1);
    if (strCopy == NULL) {
        return tuple;
    }

    memcpy(strCopy, tupleString + 1, len - 2);
    strCopy[len - 2] = '\0';

    size_t capacity = 10;
    tuple.elements = (int*)malloc(capacity * sizeof(int));
    if (tuple.elements == NULL) {
        free(strCopy);
        return tuple;
    }

    char* token = strtok(strCopy, ",");
    while (token != NULL) {
        if (tuple.size >= capacity) {
            size_t newCapacity = capacity * 2;
            int* newData = (int*)realloc(tuple.elements, newCapacity * sizeof(int));
            if (newData == NULL) {
                free(tuple.elements);
                free(strCopy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = newData;
            capacity = newCapacity;
        }

        char* endptr;
        long val = strtol(token, &endptr, 10);
        
        if (endptr != token) {
            tuple.elements[tuple.size++] = (int)val;
        }
        
        token = strtok(NULL, ",");
    }

    free(strCopy);
    return tuple;
}

void freeIntTuple(IntTuple* tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char* tupleStr = "(1, -2, 30, 400)";
    
    IntTuple tuple = convertStringToIntTuple(tupleStr, 256);
    
    if (tuple.elements != NULL) {
        printf("Parsed Tuple: ");
        for (size_t i = 0; i < tuple.size; ++i) {
            printf("%d ", tuple.elements[i]);
        }
        printf("\n");
        freeIntTuple(&tuple);
    } else {
        printf("Failed to parse tuple string.\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *values;
    size_t length;
} IntTuple;

IntTuple string_to_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    
    if (str == NULL) {
        return tuple;
    }
    
    size_t count = 0;
    const char *p = str;
    while (*p) {
        while (*p && !isdigit((unsigned char)*p) && *p != '-') {
            p++;
        }
        if (*p) {
            count++;
            while (*p && (isdigit((unsigned char)*p) || *p == '-')) {
                p++;
            }
        }
    }
    
    if (count == 0) {
        return tuple;
    }
    
    tuple.values = (int *)malloc(count * sizeof(int));
    if (tuple.values == NULL) {
        return tuple;
    }
    
    tuple.length = count;
    size_t index = 0;
    p = str;
    
    while (*p && index < count) {
        while (*p && !isdigit((unsigned char)*p) && *p != '-') {
            p++;
        }
        if (*p) {
            char *end;
            long val = strtol(p, &end, 10);
            tuple.values[index++] = (int)val;
            p = end;
        }
    }
    
    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL && tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->length = 0;
    }
}

int main(void) {
    const char *input = "10 20 30 40 50";
    IntTuple result = string_to_tuple(input);
    
    if (result.values != NULL) {
        for (size_t i = 0; i < result.length; i++) {
            printf("%d ", result.values[i]);
        }
        printf("\n");
        free_tuple(&result);
    } else {
        printf("Failed to parse string\n");
    }
    
    return 0;
}
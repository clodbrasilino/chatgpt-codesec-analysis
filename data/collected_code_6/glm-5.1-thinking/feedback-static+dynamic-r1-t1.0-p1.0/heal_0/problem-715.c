#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

IntTuple *string_to_tuple(const char *str);
void free_tuple(IntTuple *tuple);

int main(void) {
    const char *input = "10, 20, 30, 40";
    IntTuple *tuple = string_to_tuple(input);
    
    if (tuple != NULL) {
        printf("(");
        for (size_t i = 0; i < tuple->count; i++) {
            printf("%d", tuple->elements[i]);
            if (i < tuple->count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        free_tuple(tuple);
    } else {
        printf("Conversion failed.\n");
    }
    
    return 0;
}

IntTuple *string_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    IntTuple *tuple = malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    const char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr && (isspace((unsigned char)*ptr) || *ptr == ',')) {
            ptr++;
        }
        
        if (*ptr == '\0') {
            break;
        }

        char *endptr;
        errno = 0;
        long val = strtol(ptr, &endptr, 10);

        if (errno == ERANGE || val < INT_MIN || val > INT_MAX || ptr == endptr) {
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        if (tuple->count >= SIZE_MAX / sizeof(int)) {
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        int *temp = realloc(tuple->elements, (tuple->count + 1) * sizeof(int));
        if (temp == NULL) {
            free(tuple->elements);
            free(tuple);
            return NULL;
        }

        tuple->elements = temp;
        tuple->elements[tuple->count] = (int)val;
        tuple->count++;
        
        ptr = endptr;
    }

    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}
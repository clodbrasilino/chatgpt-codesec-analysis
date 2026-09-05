#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple *string_to_int_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t length = strlen(str);
    if (length == 0) {
        return NULL;
    }

    size_t capacity = 1;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ',') {
            capacity++;
        }
    }

    int *elements = (int *)malloc(capacity * sizeof(int));
    if (elements == NULL) {
        return NULL;
    }

    size_t count = 0;
    const char *ptr = str;
    char *endptr;

    while (*ptr != '\0') {
        long val = strtol(ptr, &endptr, 10);
        
        if (endptr == ptr) {
            free(elements);
            return NULL;
        }

        /* Possible weaknesses found:
         *  'INT_MIN' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        if (val < INT_MIN || val > INT_MAX) {
            free(elements);
            return NULL;
        }

        elements[count] = (int)val;
        count++;

        ptr = endptr;
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
        }

        if (*ptr == ',') {
            ptr++;
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }
        } else if (*ptr != '\0') {
            free(elements);
            return NULL;
        }
    }

    IntTuple *tuple = (IntTuple *)malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        free(elements);
        return NULL;
    }

    tuple->elements = elements;
    tuple->size = count;

    return tuple;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *str = "10, 20, 30, 40, 50";
    IntTuple *tuple = string_to_int_tuple(str);

    if (tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return 1;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free_int_tuple(tuple);

    return 0;
}
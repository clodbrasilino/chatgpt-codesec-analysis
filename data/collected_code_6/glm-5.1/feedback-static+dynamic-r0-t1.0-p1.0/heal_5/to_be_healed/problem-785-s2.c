#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

IntTuple parse_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    if (str == NULL) {
        return tuple;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return tuple;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, str, len + 1);

    size_t capacity = 1;
    tuple.elements = (int *)malloc(capacity * sizeof(int));
    if (tuple.elements == NULL) {
        free(buffer);
        return tuple;
    }

    char *token = strtok(buffer, "(), ");
    while (token != NULL) {
        if (tuple.count >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(tuple.elements, capacity * sizeof(int));
            if (temp == NULL) {
                free(tuple.elements);
                free(buffer);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.elements = temp;
        }

        char *endptr;
        errno = 0;
        long val = strtol(token, &endptr, 10);
        if (errno == ERANGE || *endptr != '\0') {
            free(tuple.elements);
            free(buffer);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  'INT_MIN' undeclared (first use in this function)
         *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  use of undeclared identifier 'INT_MIN'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (val > INT_MAX || val < INT_MIN) {
            free(tuple.elements);
            free(buffer);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }

        tuple.elements[tuple.count++] = (int)val;
        token = strtok(NULL, "(), ");
    }

    free(buffer);

    if (tuple.count == 0) {
        free(tuple.elements);
        tuple.elements = NULL;
    } else {
        int *shrunk = (int *)realloc(tuple.elements, tuple.count * sizeof(int));
        if (shrunk != NULL) {
            tuple.elements = shrunk;
        }
    }

    return tuple;
}

int main(void) {
    const char *input = "(10, 20, 30)";
    IntTuple result = parse_tuple(input);

    if (result.elements != NULL) {
        printf("(");
        for (size_t i = 0; i < result.count; i++) {
            printf("%d", result.elements[i]);
            if (i < result.count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        free(result.elements);
    }

    return 0;
}
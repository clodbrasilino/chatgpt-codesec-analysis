#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

typedef struct {
    int *values;
    size_t count;
} IntTuple;

IntTuple* stringToIntTuple(const char *input) {
    IntTuple *tuple = (IntTuple*)malloc(sizeof(IntTuple));
    if (!tuple) return NULL;

    tuple->count = 0;
    tuple->values = NULL;

    char *input_copy = strdup(input);
    char *token = strtok(input_copy, " ,");

    while (token != NULL) {
        char *endptr;
        long value = strtol(token, &endptr, 10);

        /* Possible weaknesses found:
         *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
         *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
         */
        if (endptr == token || (*endptr != '\0' && !isspace(*endptr))) {
            free(tuple->values);
            free(tuple);
            free(input_copy);
            return NULL;
        }

        if (value < INT_MIN || value > INT_MAX) {
            free(tuple->values);
            free(tuple);
            free(input_copy);
            return NULL;
        }

        tuple->values = (int*)realloc(tuple->values, (tuple->count + 1) * sizeof(int));
        if (!tuple->values) {
            free(tuple);
            free(input_copy);
            return NULL;
        }
        tuple->values[tuple->count++] = (int)value;
        token = strtok(NULL, " ,");
    }

    free(input_copy);
    return tuple;
}

void freeIntTuple(IntTuple *tuple) {
    free(tuple->values);
    free(tuple);
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple *tuple = stringToIntTuple(input);

    if (tuple == NULL) {
        printf("Failed to create tuple\n");
        return 1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        printf("%d ", tuple->values[i]);
    }
    printf("\n");

    freeIntTuple(tuple);
    return 0;
}
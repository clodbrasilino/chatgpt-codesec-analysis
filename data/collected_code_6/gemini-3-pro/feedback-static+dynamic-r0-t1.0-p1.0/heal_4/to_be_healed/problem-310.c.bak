#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    size_t len = strlen(str);
    tuple->count = len;
    
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        tuple->elements[i] = malloc(2);
        if (tuple->elements[i]) {
            tuple->elements[i][0] = str[i];
            tuple->elements[i][1] = '\0';
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    free(tuple);
}

int main() {
    const char *input_string = "python3.0";

    Tuple *tuple = string_to_tuple(input_string);
    if (!tuple) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        printf("Element %zu: %s\n", i, tuple->elements[i]);
    }

    free_tuple(tuple);

    return EXIT_SUCCESS;
}
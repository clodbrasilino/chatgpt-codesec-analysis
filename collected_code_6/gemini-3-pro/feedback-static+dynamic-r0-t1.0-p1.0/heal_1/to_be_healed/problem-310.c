#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  */

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str || !delimiter) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    char *str_copy = strdup(str);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }

    char *saveptr;
    char *token = strtok_r(str_copy, delimiter, &saveptr);

    while (token) {
        char **new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(str_copy);
            free(tuple);
            return NULL;
        }
        tuple->elements = new_elements;

        tuple->elements[tuple->count] = strdup(token);
        if (!tuple->elements[tuple->count]) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(str_copy);
            free(tuple);
            return NULL;
        }

        tuple->count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(str_copy);
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
    const char *input_string = "apple,banana,orange,grape";
    const char *delimiter = ",";

    Tuple *tuple = string_to_tuple(input_string, delimiter);
    if (!tuple) {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        printf("Element %zu: %s\n", i, tuple->elements[i]);
    }

    free_tuple(tuple);

    return EXIT_SUCCESS;
}
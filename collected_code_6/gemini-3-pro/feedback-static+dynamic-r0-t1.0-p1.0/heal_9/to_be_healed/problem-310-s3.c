#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

Tuple* string_to_tuple(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = len;
    if (tuple->count == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char**)malloc(tuple->count * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        tuple->elements[i] = (char*)malloc(2 * sizeof(char));
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        tuple->elements[i][0] = input[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = (char*)malloc(capacity);
    if (!buffer) {
        return 1;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch == '\r') {
            continue;
        }
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = (char*)realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';

    if (length == 0 && ch == EOF) {
        free(buffer);
        return 0;
    }

    Tuple *my_tuple = string_to_tuple(buffer);
    
    if (my_tuple != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("'%s'", my_tuple->elements[i]);
            if (i < my_tuple->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(my_tuple);
    }
    
    free(buffer);
    return 0;
}
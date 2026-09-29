#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple* string_to_tuple(const char *str) {
    if (!str) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) return NULL;

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
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                if (tuple->elements[i]) {
                    free(tuple->elements[i]);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(int argc, char *argv[]) {
    char *buffer = NULL;

    if (argc > 1) {
        buffer = strdup(argv[1]);
        if (!buffer) return EXIT_FAILURE;
    } else {
        size_t capacity = 128;
        size_t length = 0;
        buffer = malloc(capacity);
        
        if (!buffer) return EXIT_FAILURE;
        
        int ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
            if (length + 1 >= capacity) {
                capacity *= 2;
                char *new_buffer = realloc(buffer, capacity);
                if (!new_buffer) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                buffer = new_buffer;
            }
            buffer[length++] = (char)ch;
        }
        buffer[length] = '\0';

        if (length == 0 && ch == EOF) {
            free(buffer);
            return EXIT_SUCCESS;
        }
    }

    Tuple *my_tuple = string_to_tuple(buffer);
    
    if (my_tuple) {
        printf("[");
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("'%s'%s", my_tuple->elements[i], i < my_tuple->count - 1 ? ", " : "");
        }
        printf("]\n");
        free_tuple(my_tuple);
    } else {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}
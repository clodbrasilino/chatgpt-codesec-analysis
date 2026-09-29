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

    size_t len = 0;
    while (str[len] != '\0') {
        if (str[len] == '\r' || str[len] == '\n') {
            break;
        }
        len++;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->count = len;
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char **)malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        tuple->elements[i] = (char *)malloc(2);
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
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(int argc, char *argv[]) {
    char *input_str = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'capacity' can be reduced. [variableScope]
     */
    size_t capacity = 1024;
    /* Possible weaknesses found:
     *  The scope of the variable 'length' can be reduced. [variableScope]
     */
    size_t length = 0;

    if (argc > 1) {
        input_str = argv[1];
    } else {
        char *buffer = (char *)malloc(capacity);
        if (!buffer) {
            return EXIT_FAILURE;
        }

        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
            if (length + 1 >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_buffer = (char *)realloc(buffer, new_capacity);
                if (!new_buffer) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                buffer = new_buffer;
                capacity = new_capacity;
            }
            buffer[length++] = (char)c;
        }
        buffer[length] = '\0';
        
        if (length == 0 && c == EOF) {
            free(buffer);
            return EXIT_SUCCESS;
        }
        input_str = buffer;
    }

    Tuple *my_tuple = string_to_tuple(input_str);

    if (my_tuple) {
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

    if (argc <= 1) {
        free(input_str);
    }

    return EXIT_SUCCESS;
}
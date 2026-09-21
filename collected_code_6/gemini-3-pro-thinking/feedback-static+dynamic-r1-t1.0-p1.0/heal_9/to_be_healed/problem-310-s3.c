#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}
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
    while (len < 1048576 && str[len] != '\0') {
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
        if (!tuple->elements[i]) {
            tuple->count = i;
            free_tuple(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void print_tuple(const Tuple *tuple) {
    if (!tuple) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    const char *input = NULL;
    char *buffer = NULL;

    if (argc > 1) {
        input = argv[1];
    } else {
        size_t size = 1024;
        size_t len = 0;
        buffer = (char *)malloc(size);
        if (!buffer) {
            return EXIT_FAILURE;
        }

        int ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
            if (len >= size - 1) {
                size_t new_size = size * 2;
                if (new_size <= size) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                size = new_size;
                char *new_buf = (char *)realloc(buffer, size);
                if (!new_buf) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                buffer = new_buf;
            }
            buffer[len++] = (char)ch;
        }
        
        if (len == 0 && ch == EOF) {
            free(buffer);
            return EXIT_SUCCESS;
        }
        
        buffer[len] = '\0';
        input = buffer;
    }

    Tuple *tuple = string_to_tuple(input);
    if (tuple) {
        print_tuple(tuple);
        free_tuple(tuple);
    }

    if (buffer) {
        free(buffer);
    }

    return EXIT_SUCCESS;
}
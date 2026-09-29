#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

Tuple* string_to_tuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = strlen(str);
    if (tuple->count == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(tuple->count * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        tuple->elements[i] = malloc(2 * sizeof(char));
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void free_tuple(Tuple* tuple) {
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

int main(int argc, char *argv[]) {
    char buffer[1024];
    const char *input = NULL;

    if (argc > 1) {
        input = argv[1];
    } else {
        if (scanf("%1023[^\n]", buffer) == 1 || scanf("%1023s", buffer) == 1) {
            input = buffer;
        }
    }

    if (input != NULL) {
        Tuple* tuple = string_to_tuple(input);

        if (tuple != NULL) {
            printf("[");
            for (size_t i = 0; i < tuple->count; i++) {
                printf("'%s'", tuple->elements[i]);
                if (i < tuple->count - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
            free_tuple(tuple);
        }
    }

    return 0;
}
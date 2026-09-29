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

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len > 0) {
        tuple->elements = (char **)malloc(len * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = (char *)malloc(2 * sizeof(char));
            if (!tuple->elements[i]) {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->elements[j]);
                }
                free(tuple->elements);
                free(tuple);
                return NULL;
            }
            tuple->elements[i][0] = str[i];
            tuple->elements[i][1] = '\0';
            tuple->count++;
        }
    }
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *input_string = "python3.0";

    Tuple *my_tuple = string_to_tuple(input_string);

    if (my_tuple) {
        printf("[");
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("'%s'%s", my_tuple->elements[i], (i < my_tuple->count - 1) ? ", " : "");
        }
        printf("]\n");
        free_tuple(my_tuple);
    }

    return 0;
}
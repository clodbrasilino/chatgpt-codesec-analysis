#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  */

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (!delimiter || *delimiter == '\0') {
        size_t len = strlen(str);
        if (len > 0) {
            tuple->elements = malloc(len * sizeof(char *));
            if (!tuple->elements) {
                free(tuple);
                return NULL;
            }
            for (size_t i = 0; i < len; i++) {
                tuple->elements[i] = malloc(2);
                if (!tuple->elements[i]) {
                    for (size_t j = 0; j < tuple->count; j++) {
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

    size_t str_len = strlen(str);
    char *str_copy = malloc(str_len + 1);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }
    strcpy(str_copy, str);

    char *token = strtok(str_copy, delimiter);

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

        size_t tok_len = strlen(token);
        tuple->elements[tuple->count] = malloc(tok_len + 1);
        if (!tuple->elements[tuple->count]) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(str_copy);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->elements[tuple->count], token);

        tuple->count++;
        token = strtok(NULL, delimiter);
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

void print_tuple(Tuple *tuple) {
    if (!tuple) return;
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

int main(void) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strcspn(buffer, "\r\n");
        buffer[len] = '\0';

        Tuple *tuple = string_to_tuple(buffer, NULL);
        if (tuple) {
            print_tuple(tuple);
            free_tuple(tuple);
        }
    }
    return EXIT_SUCCESS;
}
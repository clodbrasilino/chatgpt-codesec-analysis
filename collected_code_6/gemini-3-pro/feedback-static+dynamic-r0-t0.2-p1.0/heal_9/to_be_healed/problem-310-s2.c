#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  */

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str) {
        return NULL;
    }

    if (!delimiter) {
        delimiter = "";
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (delimiter[0] == '\0') {
        size_t len = strlen(str);
        if (len == 0) {
            return tuple;
        }
        tuple->elements = malloc(len * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        tuple->count = len;
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i]) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
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

    while (token != NULL) {
        char **new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!new_elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
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
            free(tuple);
            free(str_copy);
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
    if (tuple) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    char buffer[1024];

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            Tuple *my_tuple = string_to_tuple(argv[i], "");
            if (my_tuple) {
                if (my_tuple->count == 0) {
                    printf("[]\n");
                } else {
                    printf("[");
                    for (size_t j = 0; j < my_tuple->count; j++) {
                        printf("'%s'", my_tuple->elements[j]);
                        if (j < my_tuple->count - 1) {
                            printf(", ");
                        }
                    }
                    printf("]\n");
                }
                free_tuple(my_tuple);
            } else {
                printf("[]\n");
            }
        }
        return EXIT_SUCCESS;
    }

    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }

        Tuple *my_tuple = string_to_tuple(buffer, "");

        if (my_tuple) {
            if (my_tuple->count == 0) {
                printf("[]\n");
            } else {
                printf("[");
                for (size_t i = 0; i < my_tuple->count; i++) {
                    printf("'%s'", my_tuple->elements[i]);
                    if (i < my_tuple->count - 1) {
                        printf(", ");
                    }
                }
                printf("]\n");
            }
            free_tuple(my_tuple);
        } else {
            printf("[]\n");
        }
    }

    return EXIT_SUCCESS;
}
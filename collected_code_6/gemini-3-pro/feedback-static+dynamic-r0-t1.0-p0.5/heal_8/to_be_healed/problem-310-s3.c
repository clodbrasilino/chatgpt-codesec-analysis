#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  */

Tuple* string_to_tuple(const char *str, const char *delimiter) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (!delimiter || delimiter[0] == '\0') {
        size_t len = strlen(str);
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
            }
            tuple->count = len;
        }
        return tuple;
    }

    char *str_copy = strdup(str);
    if (!str_copy) {
        free(tuple);
        return NULL;
    }

    char *token = strtok(str_copy, delimiter);
    while (token) {
        char **temp = (char **)realloc(tuple->elements, (tuple->count + 1) * sizeof(char *));
        if (!temp) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->elements = temp;
        tuple->elements[tuple->count] = strdup(token);
        if (!tuple->elements[tuple->count]) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->count++;
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
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
    char str[1024];
    const char *target_str = "python3.0";

    if (argc > 1) {
        target_str = argv[1];
    } else {
        if (scanf("%1023s", str) == 1) {
            target_str = str;
        }
    }

    const char *delimiter = "";
    Tuple *tuple = string_to_tuple(target_str, delimiter);

    if (tuple) {
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

    return 0;
}
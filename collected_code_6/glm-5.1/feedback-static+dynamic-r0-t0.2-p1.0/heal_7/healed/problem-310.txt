#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    if (str[0] == '\0') {
        return tuple;
    }

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);

    while (token != NULL) {
        size_t token_len = strlen(token);
        char **new_items = realloc(tuple->items, (tuple->count + token_len) * sizeof(char *));
        if (new_items == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;

        for (size_t i = 0; i < token_len; i++) {
            char *ch = malloc(2);
            if (ch == NULL) {
                for (size_t k = 0; k < tuple->count; k++) {
                    free(tuple->items[k]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            ch[0] = token[i];
            ch[1] = '\0';
            tuple->items[tuple->count + i] = ch;
        }

        tuple->count += token_len;
        token = strtok_r(NULL, delim, &rest);
    }

    free(temp);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}

int main(void) {
    const char *test_cases[][2] = {
        {"python3.0", "."},
        {"item1", "-"},
        {"1.10", "."}
    };

    for (int i = 0; i < 3; i++) {
        Tuple *t = string_to_tuple(test_cases[i][0], test_cases[i][1]);
        if (t != NULL) {
            printf("Test %d: [", i);
            for (size_t j = 0; j < t->count; j++) {
                printf("'%s'", t->items[j]);
                if (j < t->count - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
            free_tuple(t);
        } else {
            printf("Test %d: NULL\n", i);
        }
    }

    return EXIT_SUCCESS;
}
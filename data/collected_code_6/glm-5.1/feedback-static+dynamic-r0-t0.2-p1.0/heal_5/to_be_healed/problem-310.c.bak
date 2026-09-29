#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  */

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
        char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
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
        
        size_t token_len = strlen(token);
        if (token_len == 0) {
            token = strtok_r(NULL, delim, &rest);
            continue;
        }

        tuple->items[tuple->count] = malloc(token_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        for (size_t i = 0; i < token_len; i++) {
            tuple->items[tuple->count][i] = token[i];
            tuple->items[tuple->count][i + 1] = '\0';
            
            char **next_items = realloc(tuple->items, (tuple->count + i + 2) * sizeof(char *));
            if (next_items == NULL) {
                for (size_t k = 0; k <= tuple->count + i; k++) {
                    free(tuple->items[k]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            tuple->items = next_items;
            
            tuple->items[tuple->count + i + 1] = strdup(&token[i + 1]);
            if (tuple->items[tuple->count + i + 1] == NULL) {
                for (size_t k = 0; k <= tuple->count + i; k++) {
                    free(tuple->items[k]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    size_t capacity = 2;
    tuple->items = malloc(capacity * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    int split_by_char = 0;
    if (delim == NULL || delim[0] == '\0') {
        split_by_char = 1;
    } else {
        if (strpbrk(str, delim) == NULL) {
            split_by_char = 1;
        }
    }

    if (split_by_char) {
        for (size_t i = 0; str[i] != '\0'; i++) {
            if (tuple->count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(tuple->items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t j = 0; j < tuple->count; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items = new_items;
            }
            tuple->items[tuple->count] = malloc(2);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t j = 0; j < tuple->count; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            tuple->items[tuple->count][0] = str[i];
            tuple->items[tuple->count][1] = '\0';
            tuple->count++;
        }
    } else {
        char *tmp = strdup(str);
        if (tmp == NULL) {
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        char *saveptr;
        char *token = strtok_r(tmp, delim, &saveptr);

        while (token != NULL) {
            if (tuple->count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(tuple->items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t j = 0; j < tuple->count; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tmp);
                    free(tuple);
                    return NULL;
                }
                tuple->items = new_items;
            }

            tuple->items[tuple->count] = strdup(token);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t j = 0; j < tuple->count; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tmp);
                free(tuple);
                return NULL;
            }
            tuple->count++;
            token = strtok_r(NULL, delim, &saveptr);
        }
        free(tmp);
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    const char *delim = ",";
    
    Tuple *t = string_to_tuple(input, delim);
    if (t == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < t->count; i++) {
        printf("[%zu]: %s\n", i, t->items[i]);
    }

    free_tuple(t);
    
    return EXIT_SUCCESS;
}
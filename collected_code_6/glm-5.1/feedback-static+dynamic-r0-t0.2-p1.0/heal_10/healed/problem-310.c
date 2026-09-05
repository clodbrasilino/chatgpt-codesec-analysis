#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

size_t count_tokens(const char *str, const char *delim) {
    if (str == NULL || delim == NULL || delim[0] == '\0') {
        return 0;
    }
    size_t count = 1;
    size_t delim_len = strlen(delim);
    const char *ptr = str;
    while ((ptr = strstr(ptr, delim)) != NULL) {
        count++;
        ptr += delim_len;
    }
    return count;
}

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

    size_t total_items = count_tokens(str, delim);
    if (total_items == 0) {
        total_items = 1;
    }

    tuple->items = malloc(total_items * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple->items);
        free(tuple);
        return NULL;
    }

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);

    size_t idx = 0;
    while (token != NULL) {
        char *item = strdup(token);
        if (item == NULL) {
            for (size_t i = 0; i < idx; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items[idx] = item;
        idx++;
        token = strtok_r(NULL, delim, &rest);
    }

    tuple->count = idx;
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
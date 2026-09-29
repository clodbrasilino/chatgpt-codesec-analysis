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

    if (*delim == '\0') {
        Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
        if (tuple == NULL) {
            return NULL;
        }
        tuple->items = (char **)malloc(sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
        tuple->items[0] = strdup(str);
        if (tuple->items[0] == NULL) {
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        tuple->count = 1;
        return tuple;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    char *rest = temp;
    char *token;
    size_t delim_len = strlen(delim);

    if (delim_len == 1) {
        token = strtok_r(rest, delim, &rest);
    } else {
        token = strstr(rest, delim);
    }

    while (token != NULL) {
        char *item_str;
        if (delim_len == 1) {
            item_str = token;
        } else {
            size_t token_len = token - rest;
            item_str = (char *)malloc(token_len + 1);
            if (item_str == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            memcpy(item_str, rest, token_len);
            item_str[token_len] = '\0';
            rest = token + delim_len;
        }

        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            if (delim_len > 1) {
                free(item_str);
            }
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        tuple->items = new_items;
        
        if (delim_len == 1) {
            tuple->items[tuple->count] = strdup(item_str);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
        } else {
            tuple->items[tuple->count] = item_str;
        }

        tuple->count++;

        if (delim_len == 1) {
            token = strtok_r(rest, delim, &rest);
        } else {
            token = strstr(rest, delim);
        }
    }

    if (delim_len > 1 && *rest != '\0') {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
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
        tuple->items[tuple->count] = strdup(rest);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;
    } else if (delim_len == 1 && *rest != '\0') {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
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
        tuple->items[tuple->count] = strdup(rest);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;
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
    const char *inputs[] = {"python3.0", "item1", "15.10"};
    const char *delimiter = "";

    for (int i = 0; i < 3; i++) {
        Tuple *my_tuple = string_to_tuple(inputs[i], delimiter);
        if (my_tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }

        printf("Tuple count: %zu\n", my_tuple->count);
        for (size_t j = 0; j < my_tuple->count; j++) {
            printf("Item %zu: %s\n", j, my_tuple->items[j]);
        }

        free_tuple(my_tuple);
        printf("\n");
    }

    const char *csv = "apple,banana,cherry";
    Tuple *csv_tuple = string_to_tuple(csv, ",");
    if (csv_tuple != NULL) {
        printf("Tuple count: %zu\n", csv_tuple->count);
        for (size_t j = 0; j < csv_tuple->count; j++) {
            printf("Item %zu: %s\n", j, csv_tuple->items[j]);
        }
        free_tuple(csv_tuple);
    }

    return EXIT_SUCCESS;
}
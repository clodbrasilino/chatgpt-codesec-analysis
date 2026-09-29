#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

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

        char *token = strtok(tmp, delim);

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
            token = strtok(NULL, delim);
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

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char *str = argv[1];
        char *delim = "";
        if (argc > 2) {
            delim = argv[2];
        }

        Tuple *t = string_to_tuple(str, delim);
        if (t == NULL) {
            return EXIT_FAILURE;
        }

        printf("[");
        for (size_t i = 0; i < t->count; i++) {
            printf("'%s'", t->items[i]);
            if (i < t->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        free_tuple(t);
    } else {
        char *str = NULL;
        char *delim_buf = NULL;
        size_t str_buf_size = 0;
        size_t delim_buf_size = 0;

        while (1) {
            ssize_t str_len = getline(&str, &str_buf_size, stdin);
            if (str_len == -1) {
                break;
            }
            if (str_len > 0 && str[str_len - 1] == '\n') {
                str[str_len - 1] = '\0';
            }

            ssize_t delim_len = getline(&delim_buf, &delim_buf_size, stdin);
            char *delim;
            if (delim_len == -1) {
                delim = "";
            } else {
                delim = delim_buf;
                if (delim_len > 0 && delim[delim_len - 1] == '\n') {
                    delim[delim_len - 1] = '\0';
                }
            }

            Tuple *t = string_to_tuple(str, delim);
            if (t == NULL) {
                printf("[]\n");
            } else {
                printf("[");
                for (size_t i = 0; i < t->count; i++) {
                    printf("'%s'", t->items[i]);
                    if (i < t->count - 1) {
                        printf(", ");
                    }
                }
                printf("]\n");
                free_tuple(t);
            }
        }
        free(str);
        free(delim_buf);
    }

    return EXIT_SUCCESS;
}
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

    int split_by_char = 0;
    if (delim == NULL || delim[0] == '\0') {
        split_by_char = 1;
    } else {
        if (strpbrk(str, delim) == NULL) {
            split_by_char = 1;
        }
    }

    if (split_by_char) {
        size_t len = strlen(str);
        if (len > 0) {
            tuple->items = malloc(len * sizeof(char *));
            if (tuple->items == NULL) {
                free(tuple);
                return NULL;
            }
            for (size_t i = 0; i < len; i++) {
                tuple->items[i] = malloc(2);
                if (tuple->items[i] == NULL) {
                    for (size_t j = 0; j < i; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items[i][0] = str[i];
                tuple->items[i][1] = '\0';
            }
            tuple->count = len;
        }
    } else {
        size_t len = strlen(str) + 1;
        char *tmp = malloc(len);
        if (tmp == NULL) {
            free(tuple);
            return NULL;
        }
        memcpy(tmp, str, len);

        size_t token_count = 0;
        char *token = strtok(tmp, delim);
        while (token != NULL) {
            token_count++;
            token = strtok(NULL, delim);
        }

        if (token_count > 0) {
            tuple->items = malloc(token_count * sizeof(char *));
            if (tuple->items == NULL) {
                free(tmp);
                free(tuple);
                return NULL;
            }

            memcpy(tmp, str, len);
            token = strtok(tmp, delim);
            while (token != NULL) {
                size_t tlen = strlen(token) + 1;
                tuple->items[tuple->count] = malloc(tlen);
                if (tuple->items[tuple->count] == NULL) {
                    for (size_t j = 0; j < tuple->count; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tmp);
                    free(tuple);
                    return NULL;
                }
                memcpy(tuple->items[tuple->count], token, tlen);
                tuple->count++;
                token = strtok(NULL, delim);
            }
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
    char str_buf[4096] = {0};
    char delim_buf[4096] = {0};
    
    if (fgets(str_buf, sizeof(str_buf), stdin)) {
        str_buf[strcspn(str_buf, "\n")] = '\0';
    }
    if (fgets(delim_buf, sizeof(delim_buf), stdin)) {
        delim_buf[strcspn(delim_buf, "\n")] = '\0';
    }
    
    Tuple *t = string_to_tuple(str_buf, delim_buf);
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
    return EXIT_SUCCESS;
}
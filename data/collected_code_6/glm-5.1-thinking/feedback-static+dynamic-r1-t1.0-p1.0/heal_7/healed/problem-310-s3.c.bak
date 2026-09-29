#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str, const char *delim) {
    (void)delim;
    if (str == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

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
        str_buf[strcspn(str_buf, "\r\n")] = '\0';
    }
    if (fgets(delim_buf, sizeof(delim_buf), stdin)) {
        delim_buf[strcspn(delim_buf, "\r\n")] = '\0';
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
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

int collection_init(Collection *col, size_t capacity) {
    if (!col || capacity == 0) {
        return 0;
    }
    col->items = malloc(capacity * sizeof(char *));
    if (!col->items) {
        return 0;
    }
    col->size = 0;
    col->capacity = capacity;
    return 1;
}

int collection_contains(Collection *col, const char *item) {
    if (!col || !item) {
        return 0;
    }
    for (size_t i = 0; i < col->size; i++) {
        if (strcmp(col->items[i], item) == 0) {
            return 1;
        }
    }
    return 0;
}

int collection_add(Collection *col, const char *item) {
    if (!col || !item) {
        return 0;
    }
    if (collection_contains(col, item)) {
        return 1;
    }
    if (col->size == col->capacity) {
        size_t new_cap = col->capacity * 2;
        char **new_items = realloc(col->items, new_cap * sizeof(char *));
        if (!new_items) {
            return 0;
        }
        col->items = new_items;
        col->capacity = new_cap;
    }
    char *new_item = strdup(item);
    if (!new_item) {
        return 0;
    }
    col->items[col->size++] = new_item;
    return 1;
}

void collection_free(Collection *col) {
    if (!col) {
        return;
    }
    for (size_t i = 0; i < col->size; i++) {
        free(col->items[i]);
    }
    free(col->items);
    col->items = NULL;
    col->size = 0;
    col->capacity = 0;
}

int remove_duplicate_words(char *str) {
    if (!str) {
        return 0;
    }
    if (*str == '\0') {
        return 1;
    }

    Collection col;
    if (!collection_init(&col, 16)) {
        return 0;
    }

    char *str_copy = strdup(str);
    if (!str_copy) {
        collection_free(&col);
        return 0;
    }

    char *saveptr = NULL;
    char *token = strtok_r(str_copy, " \t\n", &saveptr);
    
    char *write_ptr = str;
    int is_first = 1;

    while (token != NULL) {
        if (!collection_contains(&col, token)) {
            if (!collection_add(&col, token)) {
                free(str_copy);
                collection_free(&col);
                return 0;
            }
            if (!is_first) {
                *write_ptr++ = ' ';
            }
            size_t len = strlen(token);
            memmove(write_ptr, token, len);
            write_ptr += len;
            is_first = 0;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }
    *write_ptr = '\0';

    free(str_copy);
    collection_free(&col);
    return 1;
}

int main(void) {
    char text[] = "this is is a test test string string with with duplicates duplicates";
    
    if (remove_duplicate_words(text)) {
        printf("%s\n", text);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
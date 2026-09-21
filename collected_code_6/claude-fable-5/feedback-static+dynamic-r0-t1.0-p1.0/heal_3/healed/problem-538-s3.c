#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096

typedef struct {
    char **items;
    size_t count;
} Tuple;

static char *duplicate_string(const char *src) {
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

Tuple *list_to_tuple(const char **list, size_t count) {
    Tuple *t;

    if (list == NULL && count > 0) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->count = count;
    t->items = NULL;

    if (count > 0) {
        if (count > SIZE_MAX / sizeof(char *)) {
            free(t);
            return NULL;
        }

        t->items = calloc(count, sizeof(char *));
        if (t->items == NULL) {
            free(t);
            return NULL;
        }

        for (size_t i = 0; i < count; i++) {
            if (list[i] == NULL) {
                t->items[i] = NULL;
                continue;
            }

            t->items[i] = duplicate_string(list[i]);
            if (t->items[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(t->items[j]);
                }
                free(t->items);
                free(t);
                return NULL;
            }
        }
    }

    return t;
}

void free_tuple(Tuple *t) {
    if (t == NULL) {
        return;
    }
    if (t->items != NULL) {
        for (size_t i = 0; i < t->count; i++) {
            free(t->items[i]);
        }
        free(t->items);
    }
    free(t);
}

void print_tuple(const Tuple *t) {
    if (t == NULL || (t->count > 0 && t->items == NULL)) {
        printf("()\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->count; i++) {
        if (t->items[i] != NULL) {
            printf("'%s'", t->items[i]);
        } else {
            printf("NULL");
        }
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    const char *list[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(list) / sizeof(list[0]);

    Tuple *t = list_to_tuple(list, count);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}
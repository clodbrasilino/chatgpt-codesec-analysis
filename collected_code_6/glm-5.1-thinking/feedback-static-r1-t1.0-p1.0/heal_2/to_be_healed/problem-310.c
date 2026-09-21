#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

void free_tuple(Tuple *t) {
    if (t == NULL) {
        return;
    }
    for (size_t i = 0; i < t->count; i++) {
        free(t->items[i]);
    }
    free(t->items);
    t->items = NULL;
    t->count = 0;
}

Tuple string_to_tuple(const char *str, char delimiter) {
    Tuple t = {NULL, 0};
    if (str == NULL) {
        return t;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return t;
    }

    char *buffer = strdup(str);
    if (buffer == NULL) {
        return t;
    }

    size_t capacity = 8;
    t.items = malloc(capacity * sizeof(char *));
    if (t.items == NULL) {
        free(buffer);
        return t;
    }

    char *token = buffer;
    char *current = buffer;

    while (*current != '\0') {
        if (*current == delimiter) {
            *current = '\0';
            if (t.count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(t.items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    free(buffer);
                    free_tuple(&t);
                    return (Tuple){NULL, 0};
                }
                t.items = new_items;
            }
            char *item = strdup(token);
            if (item == NULL) {
                free(buffer);
                free_tuple(&t);
                return (Tuple){NULL, 0};
            }
            t.items[t.count++] = item;
            token = current + 1;
        }
        current++;
    }

    if (t.count >= capacity) {
        capacity += 1;
        char **new_items = realloc(t.items, capacity * sizeof(char *));
        if (new_items == NULL) {
            free(buffer);
            free_tuple(&t);
            return (Tuple){NULL, 0};
        }
        t.items = new_items;
    }

    char *item = strdup(token);
    if (item == NULL) {
        free(buffer);
        free_tuple(&t);
        return (Tuple){NULL, 0};
    }
    t.items[t.count++] = item;

    free(buffer);
    return t;
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    Tuple t = string_to_tuple(input, ',');

    for (size_t i = 0; i < t.count; i++) {
        printf("%zu: %s\n", i, t.items[i]);
    }

    free_tuple(&t);
    return 0;
}
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

Tuple string_to_tuple(const char *str, size_t len, char delimiter) {
    Tuple t = {NULL, 0};
    if (str == NULL || len == 0) {
        return t;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return t;
    }
    memcpy(buffer, str, len);
    buffer[len] = '\0';

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
    Tuple t = string_to_tuple(input, strlen(input), ',');

    for (size_t i = 0; i < t.count; i++) {
        printf("%zu: %s\n", i, t.items[i]);
    }

    free_tuple(&t);
    return 0;
}
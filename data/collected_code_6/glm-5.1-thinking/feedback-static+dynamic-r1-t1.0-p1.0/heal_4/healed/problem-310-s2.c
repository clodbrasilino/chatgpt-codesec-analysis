#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple t = {NULL, 0};
    if (!str || *str == '\0') {
        return t;
    }

    size_t capacity = 4;
    t.items = malloc(capacity * sizeof(char *));
    if (!t.items) {
        return t;
    }

    size_t start = 0;
    size_t idx = 0;
    size_t i = 0;

    while (1) {
        if (str[i] == ',' || str[i] == '\0') {
            size_t item_len = i - start;

            if (idx >= capacity) {
                capacity *= 2;
                char **new_items = realloc(t.items, capacity * sizeof(char *));
                if (!new_items) {
                    for (size_t j = 0; j < idx; j++) {
                        free(t.items[j]);
                    }
                    free(t.items);
                    t.items = NULL;
                    t.count = 0;
                    return t;
                }
                t.items = new_items;
            }

            t.items[idx] = malloc(item_len + 1);
            if (!t.items[idx]) {
                for (size_t j = 0; j < idx; j++) {
                    free(t.items[j]);
                }
                free(t.items);
                t.items = NULL;
                t.count = 0;
                return t;
            }

            for (size_t k = 0; k < item_len; k++) {
                t.items[idx][k] = str[start + k];
            }
            t.items[idx][item_len] = '\0';
            
            idx++;

            if (str[i] == '\0') {
                break;
            }
            start = i + 1;
        }
        i++;
    }

    t.count = idx;
    return t;
}

void free_tuple(Tuple *t) {
    if (!t || !t->items) {
        return;
    }
    for (size_t i = 0; i < t->count; i++) {
        free(t->items[i]);
    }
    free(t->items);
    t->items = NULL;
    t->count = 0;
}

int main(void) {
    const char *input = "apple,banana,cherry";
    Tuple t = string_to_tuple(input);

    if (t.items) {
        for (size_t i = 0; i < t.count; i++) {
            printf("%zu: %s\n", i, t.items[i]);
        }
    }

    free_tuple(&t);

    Tuple null_t = string_to_tuple(NULL);
    free_tuple(&null_t);

    Tuple empty_t = string_to_tuple("");
    free_tuple(&empty_t);

    return 0;
}
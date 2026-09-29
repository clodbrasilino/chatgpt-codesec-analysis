#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

char *flatten_tuple_list(const TupleList *list) {
    if (list == NULL) {
        return NULL;
    }

    if (list->count == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (list->items == NULL) {
        return NULL;
    }

    size_t total = 0;

    for (size_t i = 0; i < list->count; i++) {
        int needed = snprintf(NULL, 0, "%d,%d", list->items[i].first, list->items[i].second);
        if (needed < 0) {
            return NULL;
        }

        if (i > 0) {
            if (total > SIZE_MAX - 1) {
                return NULL;
            }
            total++;
        }

        if ((size_t)needed > SIZE_MAX - total) {
            return NULL;
        }

        total += (size_t)needed;
    }

    if (total == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    char *cursor = result;

    for (size_t i = 0; i < list->count; i++) {
        if (i > 0) {
            *cursor++ = ';';
        }

        size_t remaining = total + 1 - (size_t)(cursor - result);
        int written = snprintf(cursor, remaining, "%d,%d", list->items[i].first, list->items[i].second);

        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            return NULL;
        }

        cursor += written;
    }

    *cursor = '\0';
    return result;
}

int main(void) {
    Tuple items[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    TupleList list = { items, sizeof(items) / sizeof(items[0]) };

    char *flattened = flatten_tuple_list(&list);
    if (flattened == NULL) {
        return 1;
    }

    printf("%s\n", flattened);
    free(flattened);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    size_t count;
} TupleList;

char *flatten_tuple_list(const TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t total_length = 0;
    size_t *lengths = (size_t *)malloc(list->count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list->count; i++) {
        int len = snprintf(NULL, 0, "(%d,%d)", list->tuples[i].first, list->tuples[i].second);
        if (len < 0) {
            free(lengths);
            return NULL;
        }
        lengths[i] = (size_t)len;
        total_length += lengths[i];
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < list->count; i++) {
        int written = snprintf(result + offset, lengths[i] + 1, "(%d,%d)", 
                               list->tuples[i].first, list->tuples[i].second);
        if (written < 0 || (size_t)written != lengths[i]) {
            free(lengths);
            free(result);
            return NULL;
        }
        offset += lengths[i];
    }

    result[total_length] = '\0';
    free(lengths);
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    TupleList list = {tuples, 3};

    char *flattened = flatten_tuple_list(&list);
    if (flattened == NULL) {
        fprintf(stderr, "Failed to flatten tuple list\n");
        return 1;
    }

    printf("%s\n", flattened);
    free(flattened);

    return 0;
}
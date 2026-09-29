#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    size_t size;
} TupleList;

char *flatten_tuple_list_to_string(const TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->size == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t total_length = 0;
    size_t *tuple_lengths = (size_t *)malloc(list->size * sizeof(size_t));
    if (tuple_lengths == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list->size; i++) {
        int len = snprintf(NULL, 0, "(%d,%d)", list->tuples[i].first, list->tuples[i].second);
        if (len < 0) {
            free(tuple_lengths);
            return NULL;
        }
        tuple_lengths[i] = (size_t)len;
        total_length += tuple_lengths[i];
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(tuple_lengths);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < list->size; i++) {
        int written = snprintf(result + offset, tuple_lengths[i] + 1, "(%d,%d)", 
                              list->tuples[i].first, list->tuples[i].second);
        if (written < 0 || (size_t)written != tuple_lengths[i]) {
            free(tuple_lengths);
            free(result);
            return NULL;
        }
        offset += tuple_lengths[i];
    }

    result[total_length] = '\0';
    free(tuple_lengths);
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    TupleList list = {tuples, 3};

    char *result = flatten_tuple_list_to_string(&list);
    if (result == NULL) {
        fprintf(stderr, "Failed to flatten tuple list\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    TupleList empty_list = {NULL, 0};
    char *empty_result = flatten_tuple_list_to_string(&empty_list);
    if (empty_result == NULL) {
        fprintf(stderr, "Failed to flatten empty tuple list\n");
        return 1;
    }

    printf("Empty: '%s'\n", empty_result);
    free(empty_result);

    return 0;
}
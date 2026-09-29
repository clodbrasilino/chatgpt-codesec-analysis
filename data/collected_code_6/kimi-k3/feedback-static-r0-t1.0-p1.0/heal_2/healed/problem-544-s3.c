#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

char *flatten_tuple_list(const TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return NULL;
    }

    size_t total_len = 0;
    size_t i, j;

    for (i = 0; i < list->count; i++) {
        for (j = 0; j < list->tuples[i].count; j++) {
            if (list->tuples[i].items[j] != NULL) {
                size_t len = safe_strlen(list->tuples[i].items[j], 4096);
                if (total_len + len + 1 < total_len) {
                    return NULL;
                }
                total_len += len + 1;
            }
        }
    }

    if (total_len == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t pos = 0;

    for (i = 0; i < list->count; i++) {
        for (j = 0; j < list->tuples[i].count; j++) {
            if (list->tuples[i].items[j] != NULL) {
                size_t len = safe_strlen(list->tuples[i].items[j], 4096);
                if (pos + len + 1 > total_len) {
                    free(result);
                    return NULL;
                }
                if (len > 0) {
                    memcpy(result + pos, list->tuples[i].items[j], len);
                    pos += len;
                }
                if (pos < total_len) {
                    result[pos++] = ' ';
                }
            }
        }
    }

    if (pos > 0) {
        result[pos - 1] = '\0';
    } else {
        result[pos] = '\0';
    }

    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }

    size_t i, j;
    for (i = 0; i < list->count; i++) {
        for (j = 0; j < list->tuples[i].count; j++) {
            free(list->tuples[i].items[j]);
        }
        free(list->tuples[i].items);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

static char *safe_strdup(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    size_t len = safe_strlen(s, 4096);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        memcpy(copy, s, len);
    }
    copy[len] = '\0';
    return copy;
}

int main(void) {
    TupleList list;
    list.count = 2;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    list.tuples[0].count = 2;
    list.tuples[0].items = malloc(list.tuples[0].count * sizeof(char *));
    if (list.tuples[0].items == NULL) {
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[0].items[0] = safe_strdup("Hello");
    if (list.tuples[0].items[0] == NULL) {
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[0].items[1] = safe_strdup("World");
    if (list.tuples[0].items[1] == NULL) {
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].count = 3;
    list.tuples[1].items = malloc(list.tuples[1].count * sizeof(char *));
    if (list.tuples[1].items == NULL) {
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].items[0] = safe_strdup("C");
    if (list.tuples[1].items[0] == NULL) {
        free(list.tuples[1].items);
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].items[1] = safe_strdup("Programming");
    if (list.tuples[1].items[1] == NULL) {
        free(list.tuples[1].items[0]);
        free(list.tuples[1].items);
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].items[2] = safe_strdup("Language");
    if (list.tuples[1].items[2] == NULL) {
        free(list.tuples[1].items[1]);
        free(list.tuples[1].items[0]);
        free(list.tuples[1].items);
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    char *flattened = flatten_tuple_list(&list);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    }

    free_tuple_list(&list);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static int safe_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return -1;
    }
    *result = a + b;
    return 0;
}

static int safe_copy_string(char *dest, size_t dest_size, size_t pos, const char *src, size_t len) {
    if (dest == NULL || src == NULL || pos >= dest_size) {
        return -1;
    }
    if (len > dest_size - pos - 1) {
        return -1;
    }
    if (len > 0) {
        size_t i;
        for (i = 0; i < len; i++) {
            dest[pos + i] = src[i];
        }
    }
    return 0;
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
                if (len > 0) {
                    if (safe_add_size(total_len, len + 1, &total_len) != 0) {
                        return NULL;
                    }
                }
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

    size_t alloc_size;
    if (safe_add_size(total_len, 1, &alloc_size) != 0) {
        return NULL;
    }

    char *result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t pos = 0;

    for (i = 0; i < list->count; i++) {
        for (j = 0; j < list->tuples[i].count; j++) {
            if (list->tuples[i].items[j] != NULL) {
                size_t len = safe_strlen(list->tuples[i].items[j], 4096);
                if (len > 0) {
                    if (safe_copy_string(result, alloc_size, pos, list->tuples[i].items[j], len) != 0) {
                        free(result);
                        return NULL;
                    }
                    pos += len;
                    if (pos >= alloc_size - 1) {
                        free(result);
                        return NULL;
                    }
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

static char *duplicate_string(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    size_t len = safe_strlen(s, 4096);
    if (len == 0 && s[0] != '\0') {
        return NULL;
    }
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }
    char *dup = malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }
    if (safe_copy_string(dup, len + 1, 0, s, len) != 0) {
        free(dup);
        return NULL;
    }
    dup[len] = '\0';
    return dup;
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

    list.tuples[0].items[0] = duplicate_string("Hello");
    if (list.tuples[0].items[0] == NULL) {
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[0].items[1] = duplicate_string("World");
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

    list.tuples[1].items[0] = duplicate_string("C");
    if (list.tuples[1].items[0] == NULL) {
        free(list.tuples[1].items);
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].items[1] = duplicate_string("Programming");
    if (list.tuples[1].items[1] == NULL) {
        free(list.tuples[1].items[0]);
        free(list.tuples[1].items);
        free(list.tuples[0].items[1]);
        free(list.tuples[0].items[0]);
        free(list.tuples[0].items);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].items[2] = duplicate_string("Language");
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
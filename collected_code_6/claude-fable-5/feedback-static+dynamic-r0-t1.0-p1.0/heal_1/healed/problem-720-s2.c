#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

typedef struct {
    Dict **items;
    size_t size;
} Tuple;

static Dict *dict_new(void)
{
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}

static void dict_free(Dict *dict)
{
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

static int dict_set_item(Dict *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = strdup(value);
            if (new_value == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 0;
        }
    }

    if (dict->size == dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    char *new_key = strdup(key);
    if (new_key == NULL) {
        return -1;
    }

    char *new_value = strdup(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }

    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;

    return 0;
}

static Tuple *tuple_new(size_t size)
{
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = calloc(size, sizeof(Dict *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

static void tuple_free(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }
    free(tuple->items);
    free(tuple);
}

static int add_dict_to_tuple(Tuple *tuple, size_t index, Dict *dict)
{
    if (tuple == NULL || dict == NULL) {
        return -1;
    }

    if (index >= tuple->size) {
        return -1;
    }

    tuple->items[index] = dict;

    return 0;
}

static int tuple_print(const Tuple *tuple, FILE *stream)
{
    if (tuple == NULL || stream == NULL) {
        return -1;
    }

    if (fputc('(', stream) == EOF) {
        return -1;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (i > 0) {
            if (fputs(", ", stream) == EOF) {
                return -1;
            }
        }

        Dict *dict = tuple->items[i];
        if (dict == NULL) {
            if (fputs("None", stream) == EOF) {
                return -1;
            }
            continue;
        }

        if (fputc('{', stream) == EOF) {
            return -1;
        }

        for (size_t j = 0; j < dict->size; j++) {
            if (j > 0) {
                if (fputs(", ", stream) == EOF) {
                    return -1;
                }
            }
            if (fprintf(stream, "'%s': '%s'", dict->entries[j].key, dict->entries[j].value) < 0) {
                return -1;
            }
        }

        if (fputc('}', stream) == EOF) {
            return -1;
        }
    }

    if (tuple->size == 1) {
        if (fputc(',', stream) == EOF) {
            return -1;
        }
    }

    if (fputc(')', stream) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    Tuple *tuple = NULL;
    Dict *dict = NULL;
    int status = EXIT_FAILURE;

    tuple = tuple_new(1);
    if (tuple == NULL) {
        goto cleanup;
    }

    dict = dict_new();
    if (dict == NULL) {
        goto cleanup;
    }

    if (dict_set_item(dict, "language", "C") != 0) {
        goto cleanup;
    }

    if (add_dict_to_tuple(tuple, 0, dict) != 0) {
        goto cleanup;
    }

    if (tuple_print(tuple, stdout) != 0) {
        goto cleanup;
    }

    if (printf("\n") < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dict_free(dict);
    tuple_free(tuple);

    return status;
}
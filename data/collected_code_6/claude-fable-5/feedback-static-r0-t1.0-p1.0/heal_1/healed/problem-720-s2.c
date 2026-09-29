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
    dict->capacity = 4;
    dict->size = 0;
    dict->entries = malloc(dict->capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
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
        size_t new_capacity = dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    dict->entries[dict->size].key = strdup(key);
    if (dict->entries[dict->size].key == NULL) {
        return -1;
    }
    dict->entries[dict->size].value = strdup(value);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        return -1;
    }
    dict->size++;
    return 0;
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

static Tuple *tuple_new(size_t size)
{
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->size = size;
    tuple->items = calloc(size, sizeof(Dict *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    return tuple;
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

static void tuple_free(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }
    free(tuple->items);
    free(tuple);
}

static void dict_print(const Dict *dict)
{
    printf("{");
    for (size_t i = 0; i < dict->size; i++) {
        printf("'%s': '%s'", dict->entries[i].key, dict->entries[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}");
}

static void tuple_print(const Tuple *tuple)
{
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->items[i] != NULL) {
            dict_print(tuple->items[i]);
        } else {
            printf("None");
        }
        if (tuple->size == 1 || i + 1 < tuple->size) {
            printf(",");
        }
        if (i + 1 < tuple->size) {
            printf(" ");
        }
    }
    printf(")");
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

    tuple_print(tuple);
    printf("\n");

    status = EXIT_SUCCESS;

cleanup:
    dict_free(dict);
    tuple_free(tuple);

    return status;
}
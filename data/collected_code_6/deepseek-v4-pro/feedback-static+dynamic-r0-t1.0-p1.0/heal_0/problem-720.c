#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    size_t size;
    size_t capacity;
} Tuple;

void dict_init(Dictionary *dict) {
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int dict_set(Dictionary *dict, const char *key, int value) {
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value = value;
            return 0;
        }
    }

    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 8 : dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (!new_entries) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    char *key_copy = malloc(strlen(key) + 1);
    if (!key_copy) {
        return -1;
    }
    strcpy(key_copy, key);

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

void dict_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

void tuple_init(Tuple *tuple) {
    tuple->dicts = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

int tuple_add_dict(Tuple *tuple, const Dictionary *dict) {
    if (tuple->size == tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity * 2;
        Dictionary *new_dicts = realloc(tuple->dicts, new_capacity * sizeof(Dictionary));
        if (!new_dicts) {
            return -1;
        }
        tuple->dicts = new_dicts;
        tuple->capacity = new_capacity;
    }

    Dictionary *new_dict = &tuple->dicts[tuple->size];
    dict_init(new_dict);

    for (size_t i = 0; i < dict->size; i++) {
        if (dict_set(new_dict, dict->entries[i].key, dict->entries[i].value) != 0) {
            dict_free(new_dict);
            return -1;
        }
    }

    tuple->size++;
    return 0;
}

void tuple_free(Tuple *tuple) {
    for (size_t i = 0; i < tuple->size; i++) {
        dict_free(&tuple->dicts[i]);
    }
    free(tuple->dicts);
    tuple->dicts = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

int main(void) {
    Dictionary dict;
    Tuple tuple;

    dict_init(&dict);
    tuple_init(&tuple);

    dict_set(&dict, "name", 1);
    dict_set(&dict, "age", 30);
    dict_set(&dict, "city", 3);

    if (tuple_add_dict(&tuple, &dict) != 0) {
        dict_free(&dict);
        tuple_free(&tuple);
        return 1;
    }

    printf("Tuple size: %zu\n", tuple.size);
    printf("First dictionary size: %zu\n", tuple.dicts[0].size);
    for (size_t i = 0; i < tuple.dicts[0].size; i++) {
        printf("%s: %d\n", tuple.dicts[0].entries[i].key, tuple.dicts[0].entries[i].value);
    }

    dict_free(&dict);
    tuple_free(&tuple);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} Pair;

typedef struct {
    char *key;
    char **values;
    size_t count;
    size_t capacity;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dict;

static char *string_duplicate(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

static size_t dict_find(const Dict *dict, const char *key) {
    size_t i;

    if (dict == NULL || key == NULL) {
        return (size_t)-1;
    }
    for (i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}

Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(*dict));

    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
    return dict;
}

void dict_destroy(Dict *dict) {
    size_t i;
    size_t j;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
        for (j = 0; j < dict->entries[i].count; ++j) {
            free(dict->entries[i].values[j]);
        }
        free(dict->entries[i].values);
    }
    free(dict->entries);
    free(dict);
}

int dict_insert(Dict *dict, const char *key, const char *value) {
    size_t idx;
    DictEntry *entry;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    idx = dict_find(dict, key);
    if (idx != (size_t)-1) {
        entry = &dict->entries[idx];
        if (entry->count == entry->capacity) {
            size_t new_capacity = entry->capacity == 0 ? 4 : entry->capacity * 2;
            char **new_values = realloc(entry->values, new_capacity * sizeof(*new_values));

            if (new_values == NULL) {
                return -1;
            }
            entry->values = new_values;
            entry->capacity = new_capacity;
        }
        entry->values[entry->count] = string_duplicate(value);
        if (entry->values[entry->count] == NULL) {
            return -1;
        }
        ++entry->count;
        return 0;
    }

    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 8 : dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(*new_entries));

        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    entry = &dict->entries[dict->count];
    entry->key = NULL;
    entry->values = NULL;
    entry->count = 0;
    entry->capacity = 0;

    entry->key = string_duplicate(key);
    if (entry->key == NULL) {
        return -1;
    }

    entry->values = malloc(4 * sizeof(*entry->values));
    if (entry->values == NULL) {
        free(entry->key);
        entry->key = NULL;
        return -1;
    }
    entry->capacity = 4;

    entry->values[0] = string_duplicate(value);
    if (entry->values[0] == NULL) {
        free(entry->key);
        entry->key = NULL;
        free(entry->values);
        entry->values = NULL;
        entry->capacity = 0;
        return -1;
    }
    entry->count = 1;
    ++dict->count;
    return 0;
}

Dict *group_pairs(const Pair *pairs, size_t count) {
    Dict *dict;
    size_t i;

    if (pairs == NULL && count > 0) {
        return NULL;
    }
    dict = dict_create();
    if (dict == NULL) {
        return NULL;
    }
    for (i = 0; i < count; ++i) {
        if (dict_insert(dict, pairs[i].key, pairs[i].value) != 0) {
            dict_destroy(dict);
            return NULL;
        }
    }
    return dict;
}

int main(void) {
    Pair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"animal", "dog"},
        {"fruit", "cherry"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    Dict *dict = group_pairs(pairs, count);
    size_t i;
    size_t j;

    if (dict == NULL) {
        fprintf(stderr, "Failed to group pairs\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict->count; ++i) {
        printf("%s: ", dict->entries[i].key);
        for (j = 0; j < dict->entries[i].count; ++j) {
            printf("%s%s", j > 0 ? ", " : "", dict->entries[i].values[j]);
        }
        printf("\n");
    }

    dict_destroy(dict);
    return EXIT_SUCCESS;
}
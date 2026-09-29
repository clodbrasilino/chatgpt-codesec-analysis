#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(void) {
    Dictionary *dict = malloc(sizeof(*dict));
    if (!dict) {
        return NULL;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
    return dict;
}

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t i = 0;
    if (!s) {
        return 0;
    }
    while (i < maxlen && s[i] != '\0') {
        i++;
    }
    return i;
}

static char *dict_strdup(const char *s) {
    size_t len;
    char *copy;

    if (!s) {
        return NULL;
    }
    len = safe_strnlen(s, DICT_MAX_STRING_LEN);
    if (len == DICT_MAX_STRING_LEN && s[len] != '\0') {
        return NULL;
    }
    copy = malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static int dict_reserve(Dictionary *dict, size_t new_capacity) {
    DictEntry *new_entries;

    if (new_capacity <= dict->capacity) {
        return 0;
    }
    if (new_capacity > SIZE_MAX / sizeof(DictEntry)) {
        return -1;
    }
    new_entries = realloc(dict->entries, new_capacity * sizeof(*new_entries));
    if (!new_entries) {
        return -1;
    }
    dict->entries = new_entries;
    dict->capacity = new_capacity;
    return 0;
}

static size_t dict_find(const Dictionary *dict, const char *key) {
    size_t i;

    if (!key) {
        return (size_t)-1;
    }
    for (i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}

int dict_set(Dictionary *dict, const char *key, const char *value) {
    size_t index;
    char *new_key;
    char *new_value;

    if (!dict || !key || !value) {
        return -1;
    }
    index = dict_find(dict, key);
    if (index != (size_t)-1) {
        new_value = dict_strdup(value);
        if (!new_value) {
            return -1;
        }
        free(dict->entries[index].value);
        dict->entries[index].value = new_value;
        return 0;
    }
    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 8 : dict->capacity * 2;
        if (dict_reserve(dict, new_capacity) != 0) {
            return -1;
        }
    }
    new_key = dict_strdup(key);
    if (!new_key) {
        return -1;
    }
    new_value = dict_strdup(value);
    if (!new_value) {
        free(new_key);
        return -1;
    }
    dict->entries[dict->count].key = new_key;
    dict->entries[dict->count].value = new_value;
    dict->count++;
    return 0;
}

void dict_free(Dictionary *dict) {
    size_t i;

    if (!dict) {
        return;
    }
    for (i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

Dictionary *dict_merge(const Dictionary *a, const Dictionary *b) {
    Dictionary *merged;
    size_t i;

    if (!a || !b) {
        return NULL;
    }
    merged = dict_create();
    if (!merged) {
        return NULL;
    }
    for (i = 0; i < a->count; ++i) {
        if (dict_set(merged, a->entries[i].key, a->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    for (i = 0; i < b->count; ++i) {
        if (dict_set(merged, b->entries[i].key, b->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    return merged;
}

const char *dict_get(const Dictionary *dict, const char *key) {
    size_t index;

    if (!dict || !key) {
        return NULL;
    }
    index = dict_find(dict, key);
    if (index == (size_t)-1) {
        return NULL;
    }
    return dict->entries[index].value;
}

int main(void) {
    Dictionary *dict1 = dict_create();
    Dictionary *dict2 = dict_create();
    Dictionary *merged = NULL;

    if (!dict1 || !dict2) {
        dict_free(dict1);
        dict_free(dict2);
        return 1;
    }
    if (dict_set(dict1, "name", "Alice") != 0 ||
        dict_set(dict1, "city", "Paris") != 0 ||
        dict_set(dict2, "city", "London") != 0 ||
        dict_set(dict2, "country", "UK") != 0) {
        dict_free(dict1);
        dict_free(dict2);
        return 1;
    }
    merged = dict_merge(dict1, dict2);
    if (!merged) {
        dict_free(dict1);
        dict_free(dict2);
        return 1;
    }
    printf("name=%s\n", dict_get(merged, "name"));
    printf("city=%s\n", dict_get(merged, "city"));
    printf("country=%s\n", dict_get(merged, "country"));
    dict_free(merged);
    dict_free(dict1);
    dict_free(dict2);
    return 0;
}
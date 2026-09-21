#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    size_t count;
} DictList;

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

bool all_dicts_empty(const DictList *list) {
    if (list == NULL || list->dicts == NULL || list->count == 0) {
        return true;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->dicts[i].entries != NULL && list->dicts[i].size > 0) {
            return false;
        }
    }
    return true;
}

bool dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
        return false;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return false;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return true;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                free(dict->entries[i].value);
            }
            free(dict->entries);
            dict->entries = NULL;
        }
        dict->size = 0;
        dict->capacity = 0;
    }
}

bool dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL || dict->entries == NULL) {
        return false;
    }
    if (dict->size >= dict->capacity) {
        return false;
    }

    size_t key_len = safe_strnlen(key, SIZE_MAX) + 1;
    size_t value_len = safe_strnlen(value, SIZE_MAX) + 1;

    if (key_len == 1 || value_len == 1) {
        return false;
    }

    dict->entries[dict->size].key = malloc(key_len);
    if (dict->entries[dict->size].key == NULL) {
        return false;
    }

    dict->entries[dict->size].value = malloc(value_len);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        dict->entries[dict->size].key = NULL;
        return false;
    }

    if (snprintf(dict->entries[dict->size].key, key_len, "%s", key) < 0 ||
        (size_t)snprintf(NULL, 0, "%s", key) >= key_len) {
        free(dict->entries[dict->size].key);
        free(dict->entries[dict->size].value);
        dict->entries[dict->size].key = NULL;
        dict->entries[dict->size].value = NULL;
        return false;
    }

    if (snprintf(dict->entries[dict->size].value, value_len, "%s", value) < 0 ||
        (size_t)snprintf(NULL, 0, "%s", value) >= value_len) {
        free(dict->entries[dict->size].key);
        free(dict->entries[dict->size].value);
        dict->entries[dict->size].key = NULL;
        dict->entries[dict->size].value = NULL;
        return false;
    }

    dict->size++;
    return true;
}

int main(void) {
    DictList list = {0};
    list.count = 3;
    list.dicts = calloc(list.count, sizeof(Dictionary));
    if (list.dicts == NULL) {
        return 1;
    }

    for (size_t i = 0; i < list.count; i++) {
        if (!dict_init(&list.dicts[i], 10)) {
            for (size_t j = 0; j < i; j++) {
                dict_free(&list.dicts[j]);
            }
            free(list.dicts);
            return 1;
        }
    }

    printf("All empty: %s\n", all_dicts_empty(&list) ? "true" : "false");

    if (!dict_add(&list.dicts[1], "key1", "value1")) {
        for (size_t i = 0; i < list.count; i++) {
            dict_free(&list.dicts[i]);
        }
        free(list.dicts);
        return 1;
    }

    printf("All empty: %s\n", all_dicts_empty(&list) ? "true" : "false");

    for (size_t i = 0; i < list.count; i++) {
        dict_free(&list.dicts[i]);
    }
    free(list.dicts);

    return 0;
}
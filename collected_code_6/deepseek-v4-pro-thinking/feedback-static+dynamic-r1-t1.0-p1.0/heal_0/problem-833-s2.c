#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

void dict_free(Dictionary *dict) {
    size_t i;
    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int dict_set(Dictionary *dict, const char *key, int value) {
    size_t i;
    size_t key_len;
    char *new_key;
    if (dict == NULL || key == NULL) {
        return 0;
    }
    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value = value;
            return 1;
        }
    }
    key_len = strlen(key);
    if (key_len == SIZE_MAX) {
        return 0;
    }
    if (dict->count == dict->capacity) {
        size_t new_capacity;
        Entry *new_entries;
        if (dict->capacity == 0) {
            new_capacity = 8;
            if (new_capacity > SIZE_MAX / sizeof(Entry)) {
                return 0;
            }
        } else {
            if (dict->capacity > SIZE_MAX / sizeof(Entry) / 2) {
                return 0;
            }
            new_capacity = dict->capacity * 2;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return 0;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    new_key = malloc(key_len + 1);
    if (new_key == NULL) {
        return 0;
    }
    memcpy(new_key, key, key_len + 1);
    dict->entries[dict->count].key = new_key;
    dict->entries[dict->count].value = value;
    dict->count++;
    return 1;
}

char **dict_keys(const Dictionary *dict, size_t *out_count) {
    char **keys;
    size_t i;
    if (out_count == NULL) {
        return NULL;
    }
    if (dict == NULL) {
        *out_count = 0;
        return NULL;
    }
    if (dict->count == 0) {
        *out_count = 0;
        return NULL;
    }
    *out_count = dict->count;
    if (dict->count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    keys = malloc(dict->count * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }
    for (i = 0; i < dict->count; i++) {
        size_t key_len = strlen(dict->entries[i].key);
        if (key_len == SIZE_MAX) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        keys[i] = malloc(key_len + 1);
        if (keys[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        memcpy(keys[i], dict->entries[i].key, key_len + 1);
    }
    return keys;
}

void free_keys(char **keys, size_t count) {
    size_t i;
    if (keys == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main(void) {
    Dictionary dict;
    char **keys;
    size_t count;
    size_t i;
    dict_init(&dict);
    if (!dict_set(&dict, "apple", 1)) {
        dict_free(&dict);
        return 1;
    }
    if (!dict_set(&dict, "banana", 2)) {
        dict_free(&dict);
        return 1;
    }
    if (!dict_set(&dict, "cherry", 3)) {
        dict_free(&dict);
        return 1;
    }
    keys = dict_keys(&dict, &count);
    if (keys == NULL && count != 0) {
        dict_free(&dict);
        return 1;
    }
    for (i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
    }
    free_keys(keys, count);
    dict_free(&dict);
    return 0;
}
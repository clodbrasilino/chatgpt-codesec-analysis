#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

char *my_strdup(const char *s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char *new_s = malloc(len);
    if (new_s == NULL) return NULL;
    memcpy(new_s, s, len);
    return new_s;
}

void dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL) return;
    if (capacity > 0 && capacity > SIZE_MAX / sizeof(DictEntry)) {
        exit(EXIT_FAILURE);
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL && capacity > 0) exit(EXIT_FAILURE);
    dict->size = 0;
    dict->capacity = capacity;
}

void dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL) return;
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(DictEntry)) {
            exit(EXIT_FAILURE);
        }
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) exit(EXIT_FAILURE);
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    dict->entries[dict->size].key = my_strdup(key);
    if (dict->entries[dict->size].key == NULL) exit(EXIT_FAILURE);
    if (value != NULL) {
        dict->entries[dict->size].value = my_strdup(value);
        if (dict->entries[dict->size].value == NULL) {
            free(dict->entries[dict->size].key);
            exit(EXIT_FAILURE);
        }
    } else {
        dict->entries[dict->size].value = NULL;
    }
    dict->size++;
}

void drop_empty_items(Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) return;
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < dict->size; read_idx++) {
        DictEntry *entry = &dict->entries[read_idx];
        int is_empty = (entry->key == NULL || entry->key[0] == '\0') ||
                       (entry->value == NULL || entry->value[0] == '\0');
        if (is_empty) {
            free(entry->key);
            free(entry->value);
            entry->key = NULL;
            entry->value = NULL;
        } else {
            if (write_idx != read_idx) {
                dict->entries[write_idx] = dict->entries[read_idx];
                dict->entries[read_idx].key = NULL;
                dict->entries[read_idx].value = NULL;
            }
            write_idx++;
        }
    }
    dict->size = write_idx;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict, 4);
    dict_add(&dict, "key1", "value1");
    dict_add(&dict, "", "value2");
    dict_add(&dict, "key3", "");
    dict_add(&dict, "key4", "value4");
    dict_add(&dict, "key5", NULL);
    drop_empty_items(&dict);
    for (size_t i = 0; i < dict.size; i++) {
        if (dict.entries[i].key != NULL && dict.entries[i].value != NULL) {
            printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
        }
    }
    dict_free(&dict);
    return 0;
}
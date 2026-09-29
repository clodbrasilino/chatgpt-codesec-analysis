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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s) + 1;
    char *new_s = malloc(len);
    if (new_s == NULL) return NULL;
    snprintf(new_s, len, "%s", s);
    return new_s;
}

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL) return -1;
    if (capacity == 0) {
        dict->entries = NULL;
    } else {
        dict->entries = calloc(capacity, sizeof(DictEntry));
        if (dict->entries == NULL) return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL) return -1;
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(DictEntry)) return -1;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) return -1;
        memset(new_entries + dict->capacity, 0, (new_capacity - dict->capacity) * sizeof(DictEntry));
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    dict->entries[dict->size].key = my_strdup(key);
    if (dict->entries[dict->size].key == NULL) return -1;
    if (value != NULL) {
        dict->entries[dict->size].value = my_strdup(value);
        if (dict->entries[dict->size].value == NULL) {
            free(dict->entries[dict->size].key);
            dict->entries[dict->size].key = NULL;
            return -1;
        }
    } else {
        dict->entries[dict->size].value = NULL;
    }
    dict->size++;
    return 0;
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
    int ret = EXIT_FAILURE;
    if (dict_init(&dict, 4) != 0) return EXIT_FAILURE;
    if (dict_add(&dict, "key1", "value1") != 0) goto cleanup;
    if (dict_add(&dict, "", "value2") != 0) goto cleanup;
    if (dict_add(&dict, "key3", "") != 0) goto cleanup;
    if (dict_add(&dict, "key4", "value4") != 0) goto cleanup;
    if (dict_add(&dict, "key5", NULL) != 0) goto cleanup;
    
    drop_empty_items(&dict);
    for (size_t i = 0; i < dict.size; i++) {
        if (dict.entries[i].key != NULL && dict.entries[i].value != NULL) {
            printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
        }
    }
    ret = EXIT_SUCCESS;

cleanup:
    dict_free(&dict);
    return ret;
}
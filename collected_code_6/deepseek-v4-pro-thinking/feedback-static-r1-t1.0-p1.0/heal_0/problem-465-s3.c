#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len + 1);
    return copy;
}

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return 0;
    }

    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return 0;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    char *key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return 0;
    }

    char *value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value_copy;
    dict->count++;

    return 1;
}

void drop_empty_items(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    size_t i = 0;
    while (i < dict->count) {
        int key_is_empty = dict->entries[i].key == NULL || dict->entries[i].key[0] == '\0';
        int value_is_empty = dict->entries[i].value == NULL || dict->entries[i].value[0] == '\0';

        if (key_is_empty || value_is_empty) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);

            if (i < dict->count - 1) {
                memmove(&dict->entries[i], &dict->entries[i + 1],
                        (dict->count - i - 1) * sizeof(DictEntry));
            }

            dict->count--;
        } else {
            i++;
        }
    }
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }

    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);

    if (!dict_add(&dict, "name", "Alice")) {
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!dict_add(&dict, "empty_key", "")) {
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!dict_add(&dict, "", "value")) {
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!dict_add(&dict, "age", "30")) {
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!dict_add(&dict, "", "")) {
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    drop_empty_items(&dict);

    printf("Remaining dictionary items:\n");
    for (size_t i = 0; i < dict.count; i++) {
        printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
    }

    dict_free(&dict);
    return EXIT_SUCCESS;
}
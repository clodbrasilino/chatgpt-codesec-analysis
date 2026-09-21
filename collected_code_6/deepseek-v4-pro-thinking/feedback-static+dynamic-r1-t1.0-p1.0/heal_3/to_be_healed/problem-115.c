#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

bool dictionary_init(Dictionary *dict, size_t initial_capacity) {
    if (dict == NULL) {
        return false;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;

    if (initial_capacity > 0) {
        if (initial_capacity > SIZE_MAX / sizeof(*dict->entries)) {
            return false;
        }
        dict->entries = malloc(initial_capacity * sizeof(*dict->entries));
        if (dict->entries == NULL) {
            return false;
        }
        dict->capacity = initial_capacity;
    }
    return true;
}

void dictionary_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

bool dictionary_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }

    if (dict->count == dict->capacity) {
        if (dict->capacity > SIZE_MAX / 2) {
            return false;
        }
        size_t new_capacity = dict->capacity == 0 ? 2 : dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(*dict->entries)) {
            return false;
        }
        DictionaryEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    if (key_len == SIZE_MAX) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t value_len = strlen(value);
    if (value_len == SIZE_MAX) {
        return false;
    }

    char *key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return false;
    }

    char *value_copy = malloc(value_len + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len + 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(value_copy, value, value_len + 1);

    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value_copy;
    ++dict->count;

    return true;
}

bool all_dictionaries_empty(const Dictionary * const *dictionaries, size_t count) {
    if (dictionaries == NULL) {
        return count == 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (dictionaries[i] == NULL || dictionaries[i]->count != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    Dictionary dict1, dict2, dict3;

    if (!dictionary_init(&dict1, 2) ||
        !dictionary_init(&dict2, 2) ||
        !dictionary_init(&dict3, 2)) {
        fprintf(stderr, "Failed to initialize dictionaries\n");
        dictionary_free(&dict1);
        dictionary_free(&dict2);
        dictionary_free(&dict3);
        return EXIT_FAILURE;
    }

    if (!dictionary_add(&dict1, "name", "Alice") ||
        !dictionary_add(&dict2, "city", "Paris") ||
        !dictionary_add(&dict3, "job", "Engineer")) {
        fprintf(stderr, "Failed to add entries\n");
        dictionary_free(&dict1);
        dictionary_free(&dict2);
        dictionary_free(&dict3);
        return EXIT_FAILURE;
    }

    const Dictionary * const dicts[] = { &dict1, &dict2, &dict3 };
    size_t dicts_count = sizeof(dicts) / sizeof(dicts[0]);

    if (all_dictionaries_empty(dicts, dicts_count)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Some dictionaries are not empty.\n");
    }

    dictionary_free(&dict1);
    dictionary_free(&dict2);
    dictionary_free(&dict3);

    return EXIT_SUCCESS;
}
#define __STDC_WANT_LIB_EXT1__ 1
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

bool dictionary_add(Dictionary *dict, const char *key, size_t key_len,
                    const char *value, size_t value_len) {
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
        DictionaryEntry *new_entries = realloc(dict->entries,
                                               new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    /* Possible weaknesses found:
     *  'memcpy' declared here
     */
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
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    if (memcpy_s(key_copy, key_len + 1, key, key_len) != 0) {
        free(value_copy);
        free(key_copy);
        return false;
    }
    key_copy[key_len] = '\0';

    if (memcpy_s(value_copy, value_len + 1, value, value_len) != 0) {
        free(value_copy);
        free(key_copy);
        return false;
    }
    value_copy[value_len] = '\0';

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
    Dictionary dict1 = {0};
    Dictionary dict2 = {0};
    Dictionary dict3 = {0};

    if (!dictionary_init(&dict1, 2) ||
        !dictionary_init(&dict2, 2) ||
        !dictionary_init(&dict3, 2)) {
        fprintf(stderr, "Failed to initialize dictionaries\n");
        dictionary_free(&dict1);
        dictionary_free(&dict2);
        dictionary_free(&dict3);
        return EXIT_FAILURE;
    }

    dictionary_add(&dict1, "hello", 5, "world", 5);
    dictionary_add(&dict2, "foo", 3, "bar", 3);

    const Dictionary *dictionaries[] = { &dict1, &dict2, &dict3 };
    bool empty = all_dictionaries_empty(dictionaries, 3);
    printf("All empty? %s\n", empty ? "yes" : "no");

    dictionary_free(&dict1);
    dictionary_free(&dict2);
    dictionary_free(&dict3);

    return EXIT_SUCCESS;
}
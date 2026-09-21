#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
} Dictionary;

Dictionary tuple_to_dict(char **tuple, size_t tuple_size) {
    Dictionary dict;
    dict.size = tuple_size / 2;
    dict.entries = NULL;

    if (dict.size == 0 || tuple == NULL) {
        return dict;
    }

    dict.entries = (DictEntry *)malloc(dict.size * sizeof(DictEntry));
    if (dict.entries == NULL) {
        dict.size = 0;
        return dict;
    }

    for (size_t i = 0; i < dict.size; i++) {
        char *key_src = tuple[i * 2];
        char *value_src = tuple[i * 2 + 1];

        if (key_src == NULL || value_src == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict.entries[j].key);
                free(dict.entries[j].value);
            }
            free(dict.entries);
            dict.entries = NULL;
            dict.size = 0;
            return dict;
        }

        size_t key_len = strnlen(key_src, 1024);
        size_t value_len = strnlen(value_src, 1024);

        if (key_len >= 1024 || value_len >= 1024) {
            for (size_t j = 0; j < i; j++) {
                free(dict.entries[j].key);
                free(dict.entries[j].value);
            }
            free(dict.entries);
            dict.entries = NULL;
            dict.size = 0;
            return dict;
        }

        dict.entries[i].key = (char *)malloc(key_len + 1);
        if (dict.entries[i].key == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict.entries[j].key);
                free(dict.entries[j].value);
            }
            free(dict.entries);
            dict.entries = NULL;
            dict.size = 0;
            return dict;
        }

        dict.entries[i].value = (char *)malloc(value_len + 1);
        if (dict.entries[i].value == NULL) {
            free(dict.entries[i].key);
            for (size_t j = 0; j < i; j++) {
                free(dict.entries[j].key);
                free(dict.entries[j].value);
            }
            free(dict.entries);
            dict.entries = NULL;
            dict.size = 0;
            return dict;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict.entries[i].key, key_src, key_len);
        dict.entries[i].key[key_len] = '\0';

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict.entries[i].value, value_src, value_len);
        dict.entries[i].value[value_len] = '\0';
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

int main(void) {
    char *tuple[] = {"name", "Alice", "age", "30", "city", "New York"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary dict = tuple_to_dict(tuple, tuple_size);
    if (dict.entries == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }

    for (size_t i = 0; i < dict.size; i++) {
        printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
    }

    free_dictionary(&dict);

    return 0;
}
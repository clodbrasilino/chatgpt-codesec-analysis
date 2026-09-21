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
} Dictionary;

static void free_dictionary(Dictionary *dict);

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char *safe_strdup(const char *str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = safe_strlen(str, max_len);
    if (len >= max_len) {
        return NULL;
    }
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    copy[len] = '\0';
    return copy;
}

static void free_dictionary(Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (dict->entries[i].key != NULL) {
            free(dict->entries[i].key);
            dict->entries[i].key = NULL;
        }
        if (dict->entries[i].value != NULL) {
            free(dict->entries[i].value);
            dict->entries[i].value = NULL;
        }
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

static Dictionary tuple_to_dict(char **tuple, size_t tuple_size) {
    Dictionary dict;
    dict.size = 0;
    dict.entries = NULL;

    if (tuple == NULL || tuple_size == 0 || (tuple_size % 2) != 0) {
        return dict;
    }

    dict.size = tuple_size / 2;
    
    if (dict.size > SIZE_MAX / sizeof(DictEntry)) {
        dict.size = 0;
        return dict;
    }

    dict.entries = (DictEntry *)calloc(dict.size, sizeof(DictEntry));
    if (dict.entries == NULL) {
        dict.size = 0;
        return dict;
    }

    for (size_t i = 0; i < dict.size; i++) {
        if (tuple[i * 2] == NULL) {
            free_dictionary(&dict);
            return dict;
        }

        dict.entries[i].key = safe_strdup(tuple[i * 2], 4096);
        if (dict.entries[i].key == NULL) {
            free_dictionary(&dict);
            return dict;
        }

        if (tuple[i * 2 + 1] == NULL) {
            free_dictionary(&dict);
            return dict;
        }

        dict.entries[i].value = safe_strdup(tuple[i * 2 + 1], 4096);
        if (dict.entries[i].value == NULL) {
            free_dictionary(&dict);
            return dict;
        }
    }

    return dict;
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
        if (dict.entries[i].key != NULL && dict.entries[i].value != NULL) {
            printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
        }
    }

    free_dictionary(&dict);

    return 0;
}
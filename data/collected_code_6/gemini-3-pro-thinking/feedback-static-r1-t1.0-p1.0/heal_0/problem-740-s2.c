#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *entries;
    size_t count;
} Dictionary;

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    if (dict->entries) {
        for (size_t i = 0; i < dict->count; ++i) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
    }
    free(dict);
}

char *duplicate_string(const char *str) {
    if (!str) {
        return NULL;
    }
    size_t len = strlen(str) + 1;
    char *copy = malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

Dictionary *tuple_to_dict(const char **tuple, size_t tuple_len) {
    if (!tuple || tuple_len % 2 != 0) {
        return NULL;
    }

    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->count = tuple_len / 2;
    dict->entries = malloc(dict->count * sizeof(KeyValue));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; ++i) {
        dict->entries[i].key = NULL;
        dict->entries[i].value = NULL;
    }

    for (size_t i = 0; i < dict->count; ++i) {
        if (!tuple[i * 2] || !tuple[i * 2 + 1]) {
            free_dictionary(dict);
            return NULL;
        }

        dict->entries[i].key = duplicate_string(tuple[i * 2]);
        dict->entries[i].value = duplicate_string(tuple[i * 2 + 1]);

        if (!dict->entries[i].key || !dict->entries[i].value) {
            free_dictionary(dict);
            return NULL;
        }
    }

    return dict;
}

int main(void) {
    const char *tuple[] = {
        "hostname", "localhost",
        "port", "8080",
        "protocol", "https"
    };
    
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary *dict = tuple_to_dict(tuple, tuple_len);
    if (!dict) {
        fprintf(stderr, "Failed to convert tuple to dictionary.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->count; ++i) {
        printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
    }

    free_dictionary(dict);

    return EXIT_SUCCESS;
}
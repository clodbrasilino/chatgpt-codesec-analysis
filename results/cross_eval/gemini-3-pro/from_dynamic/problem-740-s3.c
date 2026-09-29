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

Dictionary* tuple_to_dict(char **tuple, size_t tuple_len) {
    if (tuple == NULL || tuple_len % 2 != 0) {
        return NULL;
    }

    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->size = tuple_len / 2;
    dict->entries = calloc(dict->size, sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->size; i++) {
        dict->entries[i].key = strdup(tuple[i * 2]);
        if (dict->entries[i].key == NULL) {
            goto cleanup;
        }

        dict->entries[i].value = strdup(tuple[i * 2 + 1]);
        if (dict->entries[i].value == NULL) {
            free(dict->entries[i].key);
            goto cleanup;
        }
    }

    return dict;

cleanup:
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->entries[i].key) free(dict->entries[i].key);
        if (dict->entries[i].value) free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
    return NULL;
}

void free_dict(Dictionary *dict) {
    if (dict != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        free(dict);
    }
}

int main(void) {
    char *tuple[] = {"name", "Alice", "age", "25", "city", "New York"};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary *dict = tuple_to_dict(tuple, tuple_len);

    if (dict != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
        }
        free_dict(dict);
    } else {
        printf("Failed to create dictionary.\n");
    }

    return 0;
}
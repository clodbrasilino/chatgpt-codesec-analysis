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
    size_t capacity;
} Dictionary;

char **dict_keys(const Dictionary *dict, size_t *count) {
    char **keys;
    size_t i;

    if (dict == NULL || count == NULL || dict->size == 0) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    keys = malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        *count = 0;
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        keys[i] = malloc(strlen(dict->entries[i].key) + 1);
        if (keys[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            *count = 0;
            return NULL;
        }
        strcpy(keys[i], dict->entries[i].key);
    }

    *count = dict->size;
    return keys;
}

char **dict_values(const Dictionary *dict, size_t *count) {
    char **values;
    size_t i;

    if (dict == NULL || count == NULL || dict->size == 0) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    values = malloc(dict->size * sizeof(char *));
    if (values == NULL) {
        *count = 0;
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        values[i] = malloc(strlen(dict->entries[i].value) + 1);
        if (values[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(values[j]);
            }
            free(values);
            *count = 0;
            return NULL;
        }
        strcpy(values[i], dict->entries[i].value);
    }

    *count = dict->size;
    return values;
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

void free_values(char **values, size_t count) {
    size_t i;
    if (values == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(values[i]);
    }
    free(values);
}

int main(void) {
    DictEntry entries[] = {
        {"name", "Alice"},
        {"age", "30"},
        {"city", "New York"}
    };
    Dictionary dict = {entries, 3, 3};
    char **keys;
    char **values;
    size_t key_count;
    size_t value_count;
    size_t i;

    keys = dict_keys(&dict, &key_count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve dictionary keys\n");
        return EXIT_FAILURE;
    }

    values = dict_values(&dict, &value_count);
    if (values == NULL) {
        fprintf(stderr, "Failed to retrieve dictionary values\n");
        free_keys(keys, key_count);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys:\n");
    for (i = 0; i < key_count; i++) {
        printf("%s\n", keys[i]);
    }

    printf("Dictionary values:\n");
    for (i = 0; i < value_count; i++) {
        printf("%s\n", values[i]);
    }

    printf("Dictionary capacity: %zu\n", dict.capacity);

    free_keys(keys, key_count);
    free_values(values, value_count);
    return EXIT_SUCCESS;
}
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

void dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL) {
        return;
    }
    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        dict->size = 0;
        dict->capacity = 0;
        return;
    }
    dict->size = 0;
    dict->capacity = capacity;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    dict->entries[dict->size].key = malloc(strlen(key) + 1);
    if (dict->entries[dict->size].key == NULL) {
        return -1;
    }
    strcpy(dict->entries[dict->size].key, key);

    dict->entries[dict->size].value = malloc(strlen(value) + 1);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        return -1;
    }
    strcpy(dict->entries[dict->size].value, value);

    dict->size++;
    return 0;
}

void dict_free(Dictionary *dict) {
    size_t i;
    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
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

int main(void) {
    Dictionary dict;
    char **keys;
    char **values;
    size_t count;
    size_t i;

    dict_init(&dict, 3);

    if (dict_add(&dict, "name", "Alice") != 0 ||
        dict_add(&dict, "age", "30") != 0 ||
        dict_add(&dict, "city", "New York") != 0) {
        fprintf(stderr, "Failed to add dictionary entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    keys = dict_keys(&dict, &count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve dictionary keys\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
    }
    free_keys(keys, count);

    values = dict_values(&dict, &count);
    if (values == NULL) {
        fprintf(stderr, "Failed to retrieve dictionary values\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary values:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", values[i]);
    }
    free_keys(values, count);

    dict_free(&dict);
    return EXIT_SUCCESS;
}
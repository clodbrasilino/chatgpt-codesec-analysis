#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_STRING_LENGTH ((size_t)16 * 1024 * 1024)

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity);
int dict_set(Dictionary *dict, const char *key, const char *value);
const char *dict_get(const Dictionary *dict, const char *key);
Dictionary *dict_merge(const Dictionary *first, const Dictionary *second);
void dict_destroy(Dictionary *dict);
void dict_print(const Dictionary *dict);

static char *dict_strdup(const char *src)
{
    if (src == NULL) {
        return NULL;
    }
    const char *end = memchr(src, '\0', DICT_MAX_STRING_LENGTH);
    if (end == NULL) {
        return NULL;
    }
    size_t len = (size_t)(end - src) + 1;
    if (len > DICT_MAX_STRING_LENGTH) {
        return NULL;
    }
    char *copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    size_t i = 0;
    for (; i + 1 < len; i++) {
        copy[i] = src[i];
    }
    copy[i] = '\0';
    return copy;
}

Dictionary *dict_create(size_t capacity)
{
    Dictionary *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    if (capacity > 0) {
        dict->entries = calloc(capacity, sizeof(*dict->entries));
        if (dict->entries == NULL) {
            free(dict);
            return NULL;
        }
        dict->capacity = capacity;
    }
    return dict;
}

void dict_destroy(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int dict_set(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = dict_strdup(value);
            if (new_value == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 0;
        }
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        if (new_capacity < dict->capacity ||
            new_capacity > SIZE_MAX / sizeof(*dict->entries)) {
            return -1;
        }
        DictEntry *new_entries = realloc(dict->entries,
                                         new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    char *key_copy = dict_strdup(key);
    if (key_copy == NULL) {
        return -1;
    }
    char *value_copy = dict_strdup(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

const char *dict_get(const Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return dict->entries[i].value;
        }
    }
    return NULL;
}

Dictionary *dict_merge(const Dictionary *first, const Dictionary *second)
{
    if (first == NULL || second == NULL) {
        return NULL;
    }
    if (first->size > SIZE_MAX - second->size) {
        return NULL;
    }
    Dictionary *merged = dict_create(first->size + second->size);
    if (merged == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < first->size; i++) {
        if (dict_set(merged, first->entries[i].key,
                     first->entries[i].value) != 0) {
            dict_destroy(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < second->size; i++) {
        if (dict_set(merged, second->entries[i].key,
                     second->entries[i].value) != 0) {
            dict_destroy(merged);
            return NULL;
        }
    }
    return merged;
}

void dict_print(const Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    printf("{");
    for (size_t i = 0; i < dict->size; i++) {
        printf("\"%s\": \"%s\"", dict->entries[i].key, dict->entries[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Dictionary *dict_a = dict_create(4);
    if (dict_a == NULL) {
        fprintf(stderr, "Failed to create dictionary A\n");
        return EXIT_FAILURE;
    }
    Dictionary *dict_b = dict_create(4);
    if (dict_b == NULL) {
        fprintf(stderr, "Failed to create dictionary B\n");
        dict_destroy(dict_a);
        return EXIT_FAILURE;
    }
    if (dict_set(dict_a, "name", "alice") != 0 ||
        dict_set(dict_a, "lang", "c") != 0 ||
        dict_set(dict_a, "year", "1972") != 0) {
        fprintf(stderr, "Failed to populate dictionary A\n");
        dict_destroy(dict_a);
        dict_destroy(dict_b);
        return EXIT_FAILURE;
    }
    if (dict_set(dict_b, "lang", "c23") != 0 ||
        dict_set(dict_b, "os", "linux") != 0) {
        fprintf(stderr, "Failed to populate dictionary B\n");
        dict_destroy(dict_a);
        dict_destroy(dict_b);
        return EXIT_FAILURE;
    }
    Dictionary *merged = dict_merge(dict_a, dict_b);
    if (merged == NULL) {
        fprintf(stderr, "Failed to merge dictionaries\n");
        dict_destroy(dict_a);
        dict_destroy(dict_b);
        return EXIT_FAILURE;
    }
    printf("Dictionary A: ");
    dict_print(dict_a);
    printf("Dictionary B: ");
    dict_print(dict_b);
    printf("Merged:       ");
    dict_print(merged);
    const char *lang = dict_get(merged, "lang");
    if (lang != NULL) {
        printf("merged[\"lang\"] = \"%s\"\n", lang);
    }
    dict_destroy(dict_a);
    dict_destroy(dict_b);
    dict_destroy(merged);
    return EXIT_SUCCESS;
}
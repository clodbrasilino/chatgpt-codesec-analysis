#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static char *dup_string(const char *src)
{
    if (src == NULL) {
        return NULL;
    }

    const char *end = memchr(src, '\0', MAX_STR_LEN);
    if (end == NULL) {
        return NULL;
    }

    size_t len = (size_t)(end - src);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static Dict *dict_create(size_t capacity)
{
    if (capacity == 0) {
        capacity = 1;
    }
    if (capacity > SIZE_MAX / sizeof(DictEntry)) {
        return NULL;
    }

    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

static int dict_add(Dict *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (dict->size >= dict->capacity) {
        if (dict->capacity > SIZE_MAX / (2 * sizeof(DictEntry))) {
            return -1;
        }
        size_t new_capacity = dict->capacity * 2;
        DictEntry *tmp = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (tmp == NULL) {
            return -1;
        }
        dict->entries = tmp;
        dict->capacity = new_capacity;
    }

    char *key_copy = dup_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    char *value_copy = dup_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

static void dict_drop_empty(Dict *dict)
{
    size_t write_index = 0;

    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (dict->entries[i].value == NULL || dict->entries[i].value[0] == '\0') {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        } else {
            dict->entries[write_index] = dict->entries[i];
            write_index++;
        }
    }
    dict->size = write_index;
}

static void dict_print(const Dict *dict)
{
    if (dict == NULL || dict->entries == NULL) {
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

static void dict_destroy(Dict *dict)
{
    if (dict == NULL) {
        return;
    }

    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
    }
    free(dict);
}

int main(void)
{
    Dict *dict = dict_create(4);

    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "name", "Alice") != 0 ||
        dict_add(dict, "city", "") != 0 ||
        dict_add(dict, "job", "Engineer") != 0 ||
        dict_add(dict, "phone", "") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    dict_print(dict);

    dict_drop_empty(dict);

    printf("After:  ");
    dict_print(dict);

    dict_destroy(dict);
    return EXIT_SUCCESS;
}
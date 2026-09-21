#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictList;

static size_t bounded_str_length(const char *s, size_t max_len)
{
    size_t len;

    len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *safe_strdup(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = bounded_str_length(s, DICT_MAX_STRING_LEN);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static void dict_init(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

static void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
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

static int dict_set(Dictionary *dict, const char *key, const char *value)
{
    size_t i;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value;

            new_value = safe_strdup(value);
            if (new_value == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 0;
        }
    }

    if (dict->size == dict->capacity) {
        size_t new_capacity;
        DictEntry *new_entries;

        if (dict->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
            return -1;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    {
        char *new_key;
        char *new_value;

        new_key = safe_strdup(key);
        if (new_key == NULL) {
            return -1;
        }
        new_value = safe_strdup(value);
        if (new_value == NULL) {
            free(new_key);
            return -1;
        }

        dict->entries[dict->size].key = new_key;
        dict->entries[dict->size].value = new_value;
        dict->size++;
    }
    return 0;
}

static const char *dict_get(const Dictionary *dict, const char *key)
{
    size_t i;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return dict->entries[i].value;
        }
    }
    return NULL;
}

static DictList *dict_list_create(size_t count)
{
    DictList *list;
    size_t i;

    list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->items = NULL;
    list->count = 0;

    if (count == 0) {
        return list;
    }

    list->items = calloc(count, sizeof(*list->items));
    if (list->items == NULL) {
        free(list);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        dict_init(&list->items[i]);
    }
    list->count = count;
    return list;
}

static void dict_list_free(DictList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        dict_free(&list->items[i]);
    }
    free(list->items);
    free(list);
}

int main(void)
{
    DictList *list;
    const char *result;
    size_t i;

    list = dict_list_create(3);
    if (list == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return EXIT_FAILURE;
    }

    if (dict_set(&list->items[0], "language", "C") != 0) {
        fprintf(stderr, "Failed to insert entry\n");
        dict_list_free(list);
        return EXIT_FAILURE;
    }

    printf("List contains %zu dictionaries\n", list->count);
    for (i = 0; i < list->count; i++) {
        printf("Dictionary %zu has %zu entries\n", i, list->items[i].size);
    }

    result = dict_get(&list->items[0], "language");
    if (result != NULL) {
        printf("language -> %s\n", result);
    }

    dict_list_free(list);
    return EXIT_SUCCESS;
}
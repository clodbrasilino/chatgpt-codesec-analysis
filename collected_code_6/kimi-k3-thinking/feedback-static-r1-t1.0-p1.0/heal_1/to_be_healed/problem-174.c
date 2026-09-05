#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} Pair;

typedef struct {
    char *key;
    char **values;
    size_t count;
    size_t capacity;
} ValueList;

typedef struct {
    ValueList *entries;
    size_t count;
    size_t capacity;
} Dict;

static char *copy_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static ValueList *dict_find(Dict *dict, const char *key)
{
    size_t i;

    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return &dict->entries[i];
        }
    }
    return NULL;
}

static int value_list_append(ValueList *list, const char *value)
{
    char **new_values;
    char *value_copy;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (list->count == list->capacity) {
        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
            return -1;
        }
        new_values = realloc(list->values, new_capacity * sizeof(*new_values));
        if (new_values == NULL) {
            return -1;
        }
        list->values = new_values;
        list->capacity = new_capacity;
    }
    value_copy = copy_string(value);
    if (value_copy == NULL) {
        return -1;
    }
    list->values[list->count] = value_copy;
    list->count++;
    return 0;
}

static int dict_add(Dict *dict, const char *key, const char *value)
{
    ValueList *list;
    ValueList *new_entries;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    char *key_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    list = dict_find(dict, key);
    if (list != NULL) {
        return value_list_append(list, value);
    }

    if (dict->count == dict->capacity) {
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

    key_copy = copy_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    list = &dict->entries[dict->count];
    list->key = key_copy;
    list->values = NULL;
    list->count = 0;
    list->capacity = 0;

    if (value_list_append(list, value) != 0) {
        free(list->values);
        free(list->key);
        list->values = NULL;
        list->key = NULL;
        return -1;
    }
    dict->count++;
    return 0;
}

static void dict_init(Dict *dict)
{
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

static void dict_free(Dict *dict)
{
    size_t i;
    size_t j;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
        for (j = 0; j < dict->entries[i].count; j++) {
            free(dict->entries[i].values[j]);
        }
        free(dict->entries[i].values);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int group_pairs(const Pair *pairs, size_t pair_count, Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return -1;
    }
    dict_init(dict);
    if (pairs == NULL && pair_count > 0) {
        return -1;
    }
    for (i = 0; i < pair_count; i++) {
        if (pairs[i].key == NULL || pairs[i].value == NULL) {
            dict_free(dict);
            return -1;
        }
        if (dict_add(dict, pairs[i].key, pairs[i].value) != 0) {
            dict_free(dict);
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    Pair pairs[] = {
        {"fruit", "apple"},
        {"vegetable", "carrot"},
        {"fruit", "banana"},
        {"vegetable", "broccoli"},
        {"fruit", "cherry"},
        {"grain", "rice"}
    };
    Dict dict;
    size_t i;
    size_t j;

    if (group_pairs(pairs, sizeof(pairs) / sizeof(pairs[0]), &dict) != 0) {
        fprintf(stderr, "Failed to group pairs\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict.count; i++) {
        printf("%s: [", dict.entries[i].key);
        for (j = 0; j < dict.entries[i].count; j++) {
            printf("%s%s", dict.entries[i].values[j],
                   (j + 1 < dict.entries[i].count) ? ", " : "");
        }
        printf("]\n");
    }

    dict_free(&dict);
    return EXIT_SUCCESS;
}
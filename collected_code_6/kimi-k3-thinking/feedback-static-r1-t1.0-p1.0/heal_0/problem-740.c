#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s);
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

int dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return -1;
    }
    dict->pairs = NULL;
    dict->count = 0;
    dict->capacity = 0;
    if (capacity == 0) {
        return 0;
    }
    dict->pairs = (KeyValuePair *)malloc(capacity * sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        return -1;
    }
    dict->capacity = capacity;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->count >= dict->capacity) {
        return -1;
    }
    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return -1;
    }
    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    dict->pairs[dict->count].key = key_copy;
    dict->pairs[dict->count].value = value_copy;
    dict->count++;
    return 0;
}

void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    dict->pairs = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int tuple_to_dictionary(const char *tuple[], size_t tuple_size, Dictionary *dict)
{
    size_t i;
    size_t pair_count;

    if (tuple == NULL || dict == NULL) {
        return -1;
    }
    pair_count = tuple_size / 2;
    if (dict_init(dict, pair_count) != 0) {
        return -1;
    }
    for (i = 0; i + 1 < tuple_size; i += 2) {
        if (dict_add(dict, tuple[i], tuple[i + 1]) != 0) {
            dict_free(dict);
            return -1;
        }
    }
    return 0;
}

const char *dict_get(const Dictionary *dict, const char *key)
{
    size_t i;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

int main(void)
{
    const char *tuple[] = {
        "name", "Alice",
        "city", "Paris",
        "language", "C"
    };
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary dict;
    size_t i;
    const char *value;

    if (tuple_to_dictionary(tuple, tuple_size, &dict) != 0) {
        fprintf(stderr, "Failed to convert tuple to dictionary\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict.count; i++) {
        printf("%s: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }

    value = dict_get(&dict, "city");
    if (value != NULL) {
        printf("Lookup 'city': %s\n", value);
    }

    dict_free(&dict);
    return EXIT_SUCCESS;
}
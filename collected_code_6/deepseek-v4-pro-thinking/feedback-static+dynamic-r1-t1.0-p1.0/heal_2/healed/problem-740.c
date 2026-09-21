#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

static size_t safe_strlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        ++len;
    }
    return len;
}

static char *duplicate_string(const char *s) {
    char *copy;
    size_t len;

    if (s == NULL) {
        return NULL;
    }

    len = safe_strlen(s, SIZE_MAX - 1);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (snprintf(copy, len + 1, "%s", s) < 0) {
        free(copy);
        return NULL;
    }
    return copy;
}

static void free_partial_dictionary(Dictionary *dict, size_t pair_count) {
    size_t i;

    for (i = 0; i < pair_count; ++i) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

Dictionary *tuple_to_dict(const char **tuple, size_t length) {
    Dictionary *dict;
    size_t pair_count;
    size_t i;

    if (length % 2 != 0) {
        return NULL;
    }
    if (tuple == NULL && length > 0) {
        return NULL;
    }

    dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    if (length == 0) {
        dict->pairs = NULL;
        dict->count = 0;
        return dict;
    }

    pair_count = length / 2;
    dict->pairs = calloc(pair_count, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = pair_count;

    for (i = 0; i < pair_count; ++i) {
        const char *key = tuple[i * 2];
        const char *value = tuple[i * 2 + 1];

        if (key == NULL || value == NULL) {
            free_partial_dictionary(dict, i);
            return NULL;
        }

        dict->pairs[i].key = duplicate_string(key);
        if (dict->pairs[i].key == NULL) {
            free_partial_dictionary(dict, i);
            return NULL;
        }

        dict->pairs[i].value = duplicate_string(value);
        if (dict->pairs[i].value == NULL) {
            free(dict->pairs[i].key);
            free_partial_dictionary(dict, i);
            return NULL;
        }
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    free_partial_dictionary(dict, dict->count);
}

int main(void) {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Paris"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary *dict;
    size_t i;

    dict = tuple_to_dict(tuple, length);
    if (dict == NULL) {
        fprintf(stderr, "Failed to convert tuple to dictionary\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict->count; ++i) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }

    free_dictionary(dict);
    return EXIT_SUCCESS;
}
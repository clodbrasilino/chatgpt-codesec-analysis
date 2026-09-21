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
} Dictionary;

static char *safe_strdup(const char *source, size_t max_len) {
    if (source == NULL || max_len == 0) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && source[len] != '\0') {
        len++;
    }
    if (len >= max_len) {
        return NULL;
    }

    char *dest = (char *)malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    if (len > 0) {
        memcpy(dest, source, len);
    }
    dest[len] = '\0';
    return dest;
}

static void cleanup_pairs(KeyValuePair *pairs, size_t count) {
    if (pairs == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(pairs[i].key);
        free(pairs[i].value);
    }
    free(pairs);
}

Dictionary *tuple_to_dict(char **tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size == 0 || tuple_size % 2 != 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->count = tuple_size / 2;
    dict->pairs = (KeyValuePair *)calloc(dict->count, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        const char *key_source = tuple[i * 2];
        if (key_source == NULL) {
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }

        dict->pairs[i].key = safe_strdup(key_source, 4096);
        if (dict->pairs[i].key == NULL) {
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }

        const char *value_source = tuple[i * 2 + 1];
        if (value_source == NULL) {
            free(dict->pairs[i].key);
            dict->pairs[i].key = NULL;
            cleanup_pairs(dict->pairs, i + 1);
            free(dict);
            return NULL;
        }

        dict->pairs[i].value = safe_strdup(value_source, 4096);
        if (dict->pairs[i].value == NULL) {
            free(dict->pairs[i].key);
            dict->pairs[i].key = NULL;
            cleanup_pairs(dict->pairs, i + 1);
            free(dict);
            return NULL;
        }
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    cleanup_pairs(dict->pairs, dict->count);
    free(dict);
}

int main(void) {
    char *tuple[] = {"name", "John", "age", "30", "city", "New York"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary *dict = tuple_to_dict(tuple, tuple_size);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }

    for (size_t i = 0; i < dict->count; i++) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }

    free_dictionary(dict);
    return 0;
}
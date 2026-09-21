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

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Dictionary *tuple_to_dict(char **tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size < 2 || tuple_size % 2 != 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->count = tuple_size / 2;
    dict->pairs = (KeyValuePair *)malloc(dict->count * sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        if (tuple[i * 2] == NULL || tuple[i * 2 + 1] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        size_t key_len = safe_strlen(tuple[i * 2], SIZE_MAX);
        size_t value_len = safe_strlen(tuple[i * 2 + 1], SIZE_MAX);

        if (key_len >= SIZE_MAX || value_len >= SIZE_MAX) {
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        if (key_len > SIZE_MAX - 1 || value_len > SIZE_MAX - 1) {
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        dict->pairs[i].key = (char *)malloc(key_len + 1);
        if (dict->pairs[i].key == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        dict->pairs[i].value = (char *)malloc(value_len + 1);
        if (dict->pairs[i].value == NULL) {
            free(dict->pairs[i].key);
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        if (key_len + 1 < key_len || value_len + 1 < value_len) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
            for (size_t j = 0; j < i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }

        memcpy(dict->pairs[i].key, tuple[i * 2], key_len);
        dict->pairs[i].key[key_len] = '\0';
        memcpy(dict->pairs[i].value, tuple[i * 2 + 1], value_len);
        dict->pairs[i].value[value_len] = '\0';
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
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
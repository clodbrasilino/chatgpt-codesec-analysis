#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
} Dictionary;

char **get_dictionary_keys(const Dictionary *dict, size_t *out_len) {
    if (dict == NULL || out_len == NULL) {
        return NULL;
    }

    size_t len = dict->size;
    if (len == 0) {
        *out_len = 0;
        return NULL;
    }

    char **keys = malloc(len * sizeof(char *));
    if (keys == NULL) {
        *out_len = 0;
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (dict->pairs[i].key != NULL) {
            size_t key_len = strlen(dict->pairs[i].key) + 1;
            keys[i] = malloc(key_len);
            if (keys[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(keys[j]);
                }
                free(keys);
                *out_len = 0;
                return NULL;
            }
            memcpy(keys[i], dict->pairs[i].key, key_len);
        } else {
            keys[i] = NULL;
        }
    }

    *out_len = len;
    return keys;
}

void free_keys(char **keys, size_t len) {
    if (keys == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
        free(keys[i]);
    }
    free(keys);
}

char *create_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strlen(src) + 1;
    char *dest = malloc(len);
    if (dest != NULL) {
        memcpy(dest, src, len);
    }
    return dest;
}

int main(void) {
    Dictionary dict;
    dict.size = 3;
    dict.pairs = malloc(dict.size * sizeof(KeyValuePair));
    if (dict.pairs == NULL) {
        return EXIT_FAILURE;
    }

    dict.pairs[0].key = create_string("name");
    dict.pairs[0].value = create_string("Alice");
    dict.pairs[1].key = create_string("age");
    dict.pairs[1].value = create_string("30");
    dict.pairs[2].key = create_string("city");
    dict.pairs[2].value = create_string("New York");

    if (dict.pairs[0].key == NULL || dict.pairs[0].value == NULL ||
        dict.pairs[1].key == NULL || dict.pairs[1].value == NULL ||
        dict.pairs[2].key == NULL || dict.pairs[2].value == NULL) {
        for (size_t i = 0; i < dict.size; i++) {
            free(dict.pairs[i].key);
            free(dict.pairs[i].value);
        }
        free(dict.pairs);
        return EXIT_FAILURE;
    }

    size_t keys_len = 0;
    char **keys = get_dictionary_keys(&dict, &keys_len);

    if (keys != NULL) {
        for (size_t i = 0; i < keys_len; i++) {
            if (keys[i] != NULL) {
                printf("%s\n", keys[i]);
            }
        }
        free_keys(keys, keys_len);
    }

    for (size_t i = 0; i < dict.size; i++) {
        free(dict.pairs[i].key);
        free(dict.pairs[i].value);
    }
    free(dict.pairs);

    return EXIT_SUCCESS;
}
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

static void free_partial(Dictionary *dict, size_t count) {
    if (dict == NULL || dict->pairs == NULL) {
        return;
    }
    for (size_t j = 0; j < count; j++) {
        free(dict->pairs[j].key);
        free(dict->pairs[j].value);
    }
    free(dict->pairs);
    free(dict);
}

Dictionary *tuple_to_dict(char **tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size < 2 || tuple_size % 2 != 0) {
        return NULL;
    }

    size_t max_count = tuple_size / 2;
    if (max_count > SIZE_MAX / sizeof(KeyValuePair)) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->count = max_count;
    dict->pairs = (KeyValuePair *)malloc(dict->count * sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        char *key_src = tuple[i * 2];
        char *value_src = tuple[i * 2 + 1];

        if (key_src == NULL || value_src == NULL) {
            free_partial(dict, i);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_len = strlen(key_src);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t value_len = strlen(value_src);

        if (key_len > SIZE_MAX - 1) {
            free_partial(dict, i);
            return NULL;
        }

        dict->pairs[i].key = (char *)malloc(key_len + 1);
        if (dict->pairs[i].key == NULL) {
            free_partial(dict, i);
            return NULL;
        }

        if (value_len > SIZE_MAX - 1) {
            free(dict->pairs[i].key);
            free_partial(dict, i);
            return NULL;
        }

        dict->pairs[i].value = (char *)malloc(value_len + 1);
        if (dict->pairs[i].value == NULL) {
            free(dict->pairs[i].key);
            free_partial(dict, i);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->pairs[i].key, key_src, key_len + 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->pairs[i].value, value_src, value_len + 1);
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    if (dict->pairs != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
    }
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
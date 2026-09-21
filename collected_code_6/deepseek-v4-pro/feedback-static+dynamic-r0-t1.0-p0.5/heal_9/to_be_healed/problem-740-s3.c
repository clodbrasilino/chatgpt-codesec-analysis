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

static void cleanup_pairs(Dictionary *dict, size_t count) {
    if (dict == NULL) {
        return;
    }
    if (dict->pairs != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
    }
    free(dict);
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Dictionary *tuple_to_dict(char **tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size == 0 || tuple_size % 2 != 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->size = tuple_size / 2;
    dict->pairs = (KeyValuePair *)malloc(dict->size * sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->size; i++) {
        dict->pairs[i].key = NULL;
        dict->pairs[i].value = NULL;

        if (tuple[i * 2] == NULL) {
            cleanup_pairs(dict, i);
            return NULL;
        }

        size_t key_len = safe_strlen(tuple[i * 2], 4096);
        if (key_len >= 4096) {
            cleanup_pairs(dict, i);
            return NULL;
        }

        dict->pairs[i].key = (char *)malloc(key_len + 1);
        if (dict->pairs[i].key == NULL) {
            cleanup_pairs(dict, i);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->pairs[i].key, tuple[i * 2], key_len);
        dict->pairs[i].key[key_len] = '\0';

        if (tuple[i * 2 + 1] == NULL) {
            cleanup_pairs(dict, i + 1);
            return NULL;
        }

        size_t value_len = safe_strlen(tuple[i * 2 + 1], 4096);
        if (value_len >= 4096) {
            cleanup_pairs(dict, i + 1);
            return NULL;
        }

        dict->pairs[i].value = (char *)malloc(value_len + 1);
        /* Possible weaknesses found:
         *  Assuming condition 'dict->pairs[i].value==NULL' is false
         */
        if (dict->pairs[i].value == NULL) {
            cleanup_pairs(dict, i + 1);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'dict->pairs[i].value!=NULL' is always true [knownConditionTrueFalse]
         *  Condition 'dict->pairs[i].value!=NULL' is always true
         */
        if (dict->pairs[i].value != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dict->pairs[i].value, tuple[i * 2 + 1], value_len);
            dict->pairs[i].value[value_len] = '\0';
        }
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    if (dict->pairs != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
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

    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }

    free_dictionary(dict);
    return 0;
}
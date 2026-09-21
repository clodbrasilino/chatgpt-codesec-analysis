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

static void cleanup_pairs(KeyValuePair *pairs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(pairs[i].key);
        free(pairs[i].value);
    }
    free(pairs);
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
    dict->pairs = (KeyValuePair *)calloc(dict->count, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        if (tuple[i * 2] == NULL) {
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_len = strlen(tuple[i * 2]);
        /* Possible weaknesses found:
         *  key_buf_size is assigned 'key_len+1' here.
         */
        size_t key_buf_size = key_len + 1;
        /* Possible weaknesses found:
         *  Assuming condition 'key_buf_size<=key_len' is false
         *  Condition 'key_buf_size<=key_len' is always false [knownConditionTrueFalse]
         *  Condition 'key_buf_size<=key_len' is always false
         */
        if (key_buf_size <= key_len) {
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        dict->pairs[i].key = (char *)malloc(key_buf_size);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (dict->pairs[i].key == NULL) {
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'key_len>=key_buf_size' is always false [knownConditionTrueFalse]
         *  Condition 'key_len>=key_buf_size' is always false
         */
        if (key_len >= key_buf_size) {
            free(dict->pairs[i].key);
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->pairs[i].key, tuple[i * 2], key_len + 1);

        if (tuple[i * 2 + 1] == NULL) {
            free(dict->pairs[i].key);
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t value_len = strlen(tuple[i * 2 + 1]);
        /* Possible weaknesses found:
         *  value_buf_size is assigned 'value_len+1' here.
         */
        size_t value_buf_size = value_len + 1;
        /* Possible weaknesses found:
         *  Condition 'value_buf_size<=value_len' is always false
         *  Assuming condition 'value_buf_size<=value_len' is false
         *  Condition 'value_buf_size<=value_len' is always false [knownConditionTrueFalse]
         */
        if (value_buf_size <= value_len) {
            free(dict->pairs[i].key);
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        dict->pairs[i].value = (char *)malloc(value_buf_size);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (dict->pairs[i].value == NULL) {
            free(dict->pairs[i].key);
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'value_len>=value_buf_size' is always false
         *  Condition 'value_len>=value_buf_size' is always false [knownConditionTrueFalse]
         */
        if (value_len >= value_buf_size) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
            cleanup_pairs(dict->pairs, i);
            free(dict);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->pairs[i].value, tuple[i * 2 + 1], value_len + 1);
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
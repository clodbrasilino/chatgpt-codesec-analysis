#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *pairs;
    size_t count;
} Dictionary;

Dictionary tuple_to_dict(const char **tuple, size_t len) {
    Dictionary dict = {NULL, 0};
    if (tuple == NULL || len < 2) {
        return dict;
    }

    size_t pair_count = len / 2;
    dict.pairs = (KeyValue *)malloc(pair_count * sizeof(KeyValue));
    if (dict.pairs == NULL) {
        return dict;
    }

    for (size_t i = 0; i < pair_count; i++) {
        dict.pairs[i].key = strdup(tuple[i * 2]);
        dict.pairs[i].value = strdup(tuple[i * 2 + 1]);

        if (dict.pairs[i].key == NULL || dict.pairs[i].value == NULL) {
            for (size_t j = 0; j <= i; j++) {
                free(dict.pairs[j].key);
                free(dict.pairs[j].value);
            }
            free(dict.pairs);
            dict.pairs = NULL;
            dict.count = 0;
            return dict;
        }
    }

    dict.count = pair_count;
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
    dict->pairs = NULL;
    dict->count = 0;
}

int main(void) {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Wonderland"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary dict = tuple_to_dict(tuple, len);

    for (size_t i = 0; i < dict.count; i++) {
        printf("Key: %s, Value: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }

    free_dictionary(&dict);

    return 0;
}
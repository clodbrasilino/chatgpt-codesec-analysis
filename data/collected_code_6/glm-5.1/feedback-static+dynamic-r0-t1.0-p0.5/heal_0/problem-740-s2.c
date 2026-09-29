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

Dictionary *tuple_to_dict(const char **tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size % 2 != 0) {
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

    for (size_t i = 0; i < dict->size; ++i) {
        dict->pairs[i].key = strdup(tuple[i * 2]);
        dict->pairs[i].value = strdup(tuple[i * 2 + 1]);

        if (dict->pairs[i].key == NULL || dict->pairs[i].value == NULL) {
            for (size_t j = 0; j <= i; ++j) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }
    }

    return dict;
}

void free_dict(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

int main(void) {
    const char *tuple[] = {"a", "1", "b", "2", "c", "3"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary *dict = tuple_to_dict(tuple, tuple_size);
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->size; ++i) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }

    free_dict(dict);

    return EXIT_SUCCESS;
}
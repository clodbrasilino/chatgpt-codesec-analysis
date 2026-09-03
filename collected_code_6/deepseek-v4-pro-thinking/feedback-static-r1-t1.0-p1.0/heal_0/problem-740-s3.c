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

int tuple_to_dict(const char **tuple, size_t len, Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }

    dict->pairs = NULL;
    dict->count = 0;

    if (len % 2 != 0) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    if (tuple == NULL) {
        return -1;
    }

    size_t count = len / 2;

    dict->pairs = malloc(count * sizeof(KeyValue));
    if (dict->pairs == NULL) {
        return -1;
    }

    dict->count = count;

    for (size_t i = 0; i < count; i++) {
        dict->pairs[i].key = NULL;
        dict->pairs[i].value = NULL;
    }

    for (size_t i = 0; i < count; i++) {
        const char *key = tuple[2 * i];
        const char *value = tuple[2 * i + 1];

        if (key == NULL || value == NULL) {
            free_dictionary(dict);
            return -1;
        }

        dict->pairs[i].key = malloc(strlen(key) + 1);
        if (dict->pairs[i].key == NULL) {
            free_dictionary(dict);
            return -1;
        }
        strcpy(dict->pairs[i].key, key);

        dict->pairs[i].value = malloc(strlen(value) + 1);
        if (dict->pairs[i].value == NULL) {
            free_dictionary(dict);
            return -1;
        }
        strcpy(dict->pairs[i].value, value);
    }

    return 0;
}

int main(void) {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Paris"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary dict;

    if (tuple_to_dict(tuple, len, &dict) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict.count; i++) {
        printf("%s: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }

    free_dictionary(&dict);

    return EXIT_SUCCESS;
}
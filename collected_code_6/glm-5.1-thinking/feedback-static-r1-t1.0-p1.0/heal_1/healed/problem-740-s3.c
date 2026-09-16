#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    const char *value;
} KeyValue;

typedef struct {
    KeyValue *pairs;
    size_t count;
} Dictionary;

int tuple_to_dict(Dictionary *dict, const char *tuple[], size_t size) {
    if (dict == NULL) {
        return -2;
    }

    dict->pairs = NULL;
    dict->count = 0;

    if (tuple == NULL || size == 0) {
        return -2;
    }

    if (size % 2 != 0) {
        return -1;
    }

    size_t pair_count = size / 2;
    dict->pairs = malloc(pair_count * sizeof(KeyValue));

    if (dict->pairs == NULL) {
        return -3;
    }

    dict->count = pair_count;

    for (size_t i = 0; i < pair_count; i++) {
        dict->pairs[i].key = tuple[i * 2];
        dict->pairs[i].value = tuple[i * 2 + 1];
    }

    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->pairs);
        dict->pairs = NULL;
        dict->count = 0;
    }
}

int main(void) {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Wonderland"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary dict;
    int ret = tuple_to_dict(&dict, tuple, size);

    if (ret != 0) {
        if (ret == -1) {
            fprintf(stderr, "Invalid tuple size: must be even\n");
        } else if (ret == -3) {
            fprintf(stderr, "Memory allocation failed\n");
        } else {
            fprintf(stderr, "Memory allocation failed or empty tuple\n");
        }
        return 1;
    }

    for (size_t i = 0; i < dict.count; i++) {
        printf("Key: %s, Value: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }

    free_dictionary(&dict);

    return 0;
}
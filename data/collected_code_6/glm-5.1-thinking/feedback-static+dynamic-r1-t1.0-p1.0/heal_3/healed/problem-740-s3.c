#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *pairs;
    size_t count;
} Dictionary;

Dictionary tuple_to_dict(const char *tuple[], size_t size) {
    Dictionary dict = {NULL, 0};

    if (tuple == NULL || size == 0 || size % 2 != 0) {
        return dict;
    }

    size_t pair_count = size / 2;
    dict.pairs = calloc(pair_count, sizeof(KeyValue));
    
    if (dict.pairs == NULL) {
        return dict;
    }

    dict.count = pair_count;

    for (size_t i = 0; i < pair_count; i++) {
        if (tuple[i * 2] == NULL || tuple[i * 2 + 1] == NULL) {
            for (size_t j = 0; j <= i; j++) {
                free(dict.pairs[j].key);
                free(dict.pairs[j].value);
            }
            free(dict.pairs);
            dict.pairs = NULL;
            dict.count = 0;
            return dict;
        }

        size_t key_len = strnlen(tuple[i * 2], MAX_STR_LEN);
        size_t val_len = strnlen(tuple[i * 2 + 1], MAX_STR_LEN);

        dict.pairs[i].key = malloc(key_len + 1);
        dict.pairs[i].value = malloc(val_len + 1);
        
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
        
        memcpy(dict.pairs[i].key, tuple[i * 2], key_len);
        dict.pairs[i].key[key_len] = '\0';
        
        memcpy(dict.pairs[i].value, tuple[i * 2 + 1], val_len);
        dict.pairs[i].value[val_len] = '\0';
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
        dict->pairs = NULL;
        dict->count = 0;
    }
}

int main(void) {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Wonderland"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary dict = tuple_to_dict(tuple, size);

    if (dict.pairs == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return 1;
    }

    for (size_t i = 0; i < dict.count; i++) {
        printf("Key: %s, Value: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }

    free_dictionary(&dict);

    return 0;
}
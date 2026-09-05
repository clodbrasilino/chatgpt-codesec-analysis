#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dictionary_create(size_t capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->keys = (char **)malloc(capacity * sizeof(char *));
    if (dict->keys == NULL) {
        free(dict);
        return NULL;
    }
    dict->values = (char **)malloc(capacity * sizeof(char *));
    if (dict->values == NULL) {
        free(dict->keys);
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    dict->keys[dict->size] = strdup(key);
    if (dict->keys[dict->size] == NULL) {
        return -1;
    }
    dict->values[dict->size] = strdup(value);
    if (dict->values[dict->size] == NULL) {
        free(dict->keys[dict->size]);
        dict->keys[dict->size] = NULL;
        return -1;
    }
    dict->size++;
    return 0;
}

int dictionary_contains_key(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return 0;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->keys[i] != NULL && strcmp(dict->keys[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

int main(void) {
    Dictionary *dict = dictionary_create(10);
    if (dict == NULL) {
        return EXIT_FAILURE;
    }
    if (dictionary_insert(dict, "apple", "fruit") != 0) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }
    if (dictionary_insert(dict, "carrot", "vegetable") != 0) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }
    if (dictionary_insert(dict, "banana", "fruit") != 0) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }
    int found_apple = dictionary_contains_key(dict, "apple");
    int found_grape = dictionary_contains_key(dict, "grape");
    int found_null = dictionary_contains_key(NULL, "key");
    printf("apple: %d\n", found_apple);
    printf("grape: %d\n", found_grape);
    printf("null dict: %d\n", found_null);
    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}
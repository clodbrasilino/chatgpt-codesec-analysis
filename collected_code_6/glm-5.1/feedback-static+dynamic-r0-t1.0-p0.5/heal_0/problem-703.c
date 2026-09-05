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
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->keys = malloc(capacity * sizeof(char *));
    dict->values = malloc(capacity * sizeof(char *));
    if (!dict->keys || !dict->values) {
        free(dict->keys);
        free(dict->values);
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

int dictionary_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || dict->size >= dict->capacity) return 0;
    dict->keys[dict->size] = strdup(key);
    dict->values[dict->size] = strdup(value);
    if (!dict->keys[dict->size] || !dict->values[dict->size]) {
        free(dict->keys[dict->size]);
        free(dict->values[dict->size]);
        return 0;
    }
    dict->size++;
    return 1;
}

int dictionary_contains(Dictionary *dict, const char *key) {
    if (!dict || !key) return 0;
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    Dictionary *dict = dictionary_create(10);
    if (!dict) {
        return 1;
    }

    dictionary_insert(dict, "apple", "fruit");
    dictionary_insert(dict, "carrot", "vegetable");
    dictionary_insert(dict, "bread", "grain");

    const char *search_key = "carrot";
    if (dictionary_contains(dict, search_key)) {
        printf("Key '%s' found.\n", search_key);
    } else {
        printf("Key '%s' not found.\n", search_key);
    }

    search_key = "beef";
    if (dictionary_contains(dict, search_key)) {
        printf("Key '%s' found.\n", search_key);
    } else {
        printf("Key '%s' not found.\n", search_key);
    }

    dictionary_destroy(dict);
    return 0;
}
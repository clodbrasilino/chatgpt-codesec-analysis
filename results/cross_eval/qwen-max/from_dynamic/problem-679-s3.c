#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    void *value;
} DictionaryElement;

typedef struct {
    DictionaryElement *elements;
    size_t count;
} Dictionary;

void dictionary_init(Dictionary *dict) {
    dict->elements = NULL;
    dict->count = 0;
}

int dictionary_add(Dictionary *dict, const char *key, void *value) {
    if (!key || !value) return -1;

    dict->elements = realloc(dict->elements, (dict->count + 1) * sizeof(DictionaryElement));
    if (!dict->elements) return -2;

    dict->elements[dict->count].key = strdup(key);
    if (!dict->elements[dict->count].key) {
        free(dict->elements[dict->count].key);
        return -2;
    }

    dict->elements[dict->count].value = value;
    dict->count++;
    return 0;
}

void *dictionary_get_by_index(const Dictionary *dict, size_t index) {
    if (index >= dict->count) return NULL;
    return (dict->elements[index]).value;
}

void dictionary_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->elements[i].key);
    }
    free(dict->elements);
    dict->elements = NULL;
    dict->count = 0;
}

int main() {
    Dictionary dict;
    dictionary_init(&dict);

    int num1 = 42;
    int num2 = 84;

    dictionary_add(&dict, "key1", &num1);
    dictionary_add(&dict, "key2", &num2);

    void *value1 = dictionary_get_by_index(&dict, 0);
    void *value2 = dictionary_get_by_index(&dict, 1);

    if (value1 != NULL) {
        printf("Value 1: %d\n", *(int *)value1);
    }

    if (value2 != NULL) {
        printf("Value 2: %d\n", *(int *)value2);
    }

    dictionary_free(&dict);
    return 0;
}
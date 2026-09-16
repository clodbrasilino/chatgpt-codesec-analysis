#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
} DictionaryElement;

typedef struct {
    DictionaryElement **elements;
    int size;
} Dictionary;

Dictionary* create_dictionary(int size) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->elements = (DictionaryElement**)calloc(size, sizeof(DictionaryElement*));
    dict->size = size;
    return dict;
}

void insert_into_dictionary(Dictionary *dict, const char *key, void *value, int index) {
    if (index >= 0 && index < dict->size) {
        DictionaryElement *element = (DictionaryElement*)malloc(sizeof(DictionaryElement));
        element->key = strdup(key);
        element->value = value;
        dict->elements[index] = element;
    }
}

void *get_value_by_index(Dictionary *dict, int index) {
    if (index >= 0 && index < dict->size) {
        return dict->elements[index]->value;
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->elements[i] != NULL) {
            free(dict->elements[i]->key);
            free(dict->elements[i]);
        }
    }
    free(dict->elements);
    free(dict);
}

int main() {
    Dictionary *dict = create_dictionary(3);
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;

    insert_into_dictionary(dict, "one", &val1, 0);
    insert_into_dictionary(dict, "two", &val2, 1);
    insert_into_dictionary(dict, "three", &val3, 2);

    void *value = get_value_by_index(dict, 1);
    if (value != NULL) {
        printf("Value at index 1: %d\n", *(int*)value);
    }

    free_dictionary(dict);
    return 0;
}
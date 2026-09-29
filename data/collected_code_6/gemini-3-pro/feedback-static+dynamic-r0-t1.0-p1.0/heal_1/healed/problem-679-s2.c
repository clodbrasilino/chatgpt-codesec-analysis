#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* elements;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->elements = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    if (!dict->elements) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void destroy_dictionary(Dictionary* dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->elements[i].key) {
            free(dict->elements[i].key);
        }
    }
    free(dict->elements);
    free(dict);
}

int add_element(Dictionary* dict, const char* key, int value) {
    if (!dict || !key || dict->size >= dict->capacity) return -1;
    
    dict->elements[dict->size].key = strdup(key);
    if (!dict->elements[dict->size].key) return -1;
    
    dict->elements[dict->size].value = value;
    dict->size++;
    return 0;
}

const KeyValuePair* get_element_by_index(const Dictionary* dict, size_t index) {
    if (!dict || index >= dict->size) return NULL;
    return &(dict->elements[index]);
}

int main(void) {
    Dictionary* dict = create_dictionary(10);
    if (!dict) return 1;

    if (add_element(dict, "first", 100) != 0) {
        destroy_dictionary(dict);
        return 1;
    }
    
    if (add_element(dict, "second", 200) != 0) {
        destroy_dictionary(dict);
        return 1;
    }
    
    if (add_element(dict, "third", 300) != 0) {
        destroy_dictionary(dict);
        return 1;
    }

    size_t index_to_access = 1;

    const KeyValuePair* pair = get_element_by_index(dict, index_to_access);
    
    if (pair) {
        printf("Element at index %zu: Key = %s, Value = %d\n", index_to_access, pair->key, pair->value);
    } else {
        printf("Index %zu is out of bounds.\n", index_to_access);
    }

    destroy_dictionary(dict);
    return 0;
}
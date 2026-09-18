#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *elements;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->elements = (KeyValuePair *)malloc(initial_capacity * sizeof(KeyValuePair));
    if (!dict->elements) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict) {
        for (size_t i = 0; i < dict->size; ++i) {
            free(dict->elements[i].key);
        }
        free(dict->elements);
        free(dict);
    }
}

int add_element(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return -1;
    }

    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        KeyValuePair *new_elements = (KeyValuePair *)realloc(dict->elements, new_capacity * sizeof(KeyValuePair));
        if (!new_elements) {
            return -1;
        }
        dict->elements = new_elements;
        dict->capacity = new_capacity;
    }

    dict->elements[dict->size].key = strdup(key);
    if (!dict->elements[dict->size].key) {
        return -1;
    }
    
    dict->elements[dict->size].value = value;
    dict->size++;
    return 0;
}

const KeyValuePair* get_element_by_index(const Dictionary *dict, size_t index) {
    if (!dict || index >= dict->size) {
        return NULL;
    }
    return &dict->elements[index];
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return EXIT_FAILURE;
    }

    if (add_element(dict, "apple", 1) != 0) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }
    if (add_element(dict, "banana", 2) != 0) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }
    if (add_element(dict, "cherry", 3) != 0) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }

    size_t target_index = 1;
    
    const KeyValuePair *kv = get_element_by_index(dict, target_index);
    if (kv) {
        printf("Element at index %zu: Key = %s, Value = %d\n", target_index, kv->key, kv->value);
    } else {
        printf("Index %zu out of bounds or invalid dictionary.\n", target_index);
    }

    destroy_dictionary(dict);
    return EXIT_SUCCESS;
}
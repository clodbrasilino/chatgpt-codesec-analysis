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
        for (size_t i = 0; i < dict->size; i++) {
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

    char *key_copy = strdup(key);
    if (!key_copy) {
        return -1;
    }

    dict->elements[dict->size].key = key_copy;
    dict->elements[dict->size].value = value;
    dict->size++;

    return 0;
}

KeyValuePair* get_element_by_index(Dictionary *dict, size_t index) {
    if (!dict || index >= dict->size) {
        return NULL;
    }
    return &dict->elements[index];
}

int main(void) {
    Dictionary *dict = create_dictionary(2);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }

    if (add_element(dict, "First", 10) != 0) {
        destroy_dictionary(dict);
        return 1;
    }
    if (add_element(dict, "Second", 20) != 0) {
        destroy_dictionary(dict);
        return 1;
    }
    if (add_element(dict, "Third", 30) != 0) {
        destroy_dictionary(dict);
        return 1;
    }

    KeyValuePair *kvp = get_element_by_index(dict, 1);
    if (kvp) {
        printf("Index 1: Key = %s, Value = %d\n", kvp->key, kvp->value);
    } else {
        printf("Element not found at index 1\n");
    }

    kvp = get_element_by_index(dict, 5);
    if (kvp) {
        printf("Index 5: Key = %s, Value = %d\n", kvp->key, kvp->value);
    } else {
        printf("Element not found at index 5\n");
    }

    destroy_dictionary(dict);
    return 0;
}
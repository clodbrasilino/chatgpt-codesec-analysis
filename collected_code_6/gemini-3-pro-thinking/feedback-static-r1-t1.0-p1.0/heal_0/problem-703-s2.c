#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    
    dict->items = malloc(capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    if (dict->items) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
        }
        free(dict->items);
    }
    
    free(dict);
}

bool add_item(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->size >= dict->capacity) {
        return false;
    }
    
    char *key_copy = malloc(strlen(key) + 1);
    if (!key_copy) {
        return false;
    }
    strcpy(key_copy, key);
    
    dict->items[dict->size].key = key_copy;
    dict->items[dict->size].value = value;
    dict->size++;
    
    return true;
}

bool is_key_present(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return false;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return EXIT_FAILURE;
    }

    if (!add_item(dict, "apple", 1)) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }
    
    if (!add_item(dict, "banana", 2)) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }

    if (is_key_present(dict, "apple")) {
        printf("apple is present\n");
    } else {
        printf("apple is not present\n");
    }
    
    if (is_key_present(dict, "grape")) {
        printf("grape is present\n");
    } else {
        printf("grape is not present\n");
    }

    destroy_dictionary(dict);
    
    return EXIT_SUCCESS;
}
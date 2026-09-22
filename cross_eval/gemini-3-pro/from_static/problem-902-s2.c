#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    if (initial_capacity == 0) return NULL;
    
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->items = (KeyValuePair*)malloc(initial_capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

int add_or_update(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return -1;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value += value;
            return 0;
        }
    }
    
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        KeyValuePair *new_items = (KeyValuePair*)realloc(dict->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) return -1;
        
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    
    dict->items[dict->size].key = strdup(key);
    if (!dict->items[dict->size].key) return -1;
    
    dict->items[dict->size].value = value;
    dict->size++;
    
    return 0;
}

Dictionary* combine_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    if (!dict1 || !dict2) return NULL;
    
    Dictionary *result = create_dictionary(dict1->size + dict2->size);
    if (!result) return NULL;
    
    for (size_t i = 0; i < dict1->size; i++) {
        if (add_or_update(result, dict1->items[i].key, dict1->items[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }
    
    for (size_t i = 0; i < dict2->size; i++) {
        if (add_or_update(result, dict2->items[i].key, dict2->items[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }
    
    return result;
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %d\n", dict->items[i].key, dict->items[i].value);
    }
}

int main() {
    Dictionary *dict1 = create_dictionary(2);
    if (!dict1) return 1;
    
    Dictionary *dict2 = create_dictionary(2);
    if (!dict2) {
        free_dictionary(dict1);
        return 1;
    }
    
    if (add_or_update(dict1, "apple", 5) != 0 || add_or_update(dict1, "banana", 3) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    if (add_or_update(dict2, "banana", 4) != 0 || add_or_update(dict2, "orange", 2) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    Dictionary *combined = combine_dictionaries(dict1, dict2);
    if (!combined) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    print_dictionary(combined);
    
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(combined);
    
    return 0;
}
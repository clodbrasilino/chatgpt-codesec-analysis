#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->pairs = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

int add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            char *new_value = strdup(value);
            if (!new_value) return 0;
            free(dict->pairs[i].value);
            dict->pairs[i].value = new_value;
            return 1;
        }
    }
    
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        KeyValuePair *new_pairs = (KeyValuePair*)realloc(dict->pairs, new_capacity * sizeof(KeyValuePair));
        if (!new_pairs) return 0;
        dict->pairs = new_pairs;
        dict->capacity = new_capacity;
    }
    
    dict->pairs[dict->size].key = strdup(key);
    if (!dict->pairs[dict->size].key) return 0;
    
    dict->pairs[dict->size].value = strdup(value);
    if (!dict->pairs[dict->size].value) {
        free(dict->pairs[dict->size].key);
        return 0;
    }
    
    dict->size++;
    return 1;
}

Dictionary* merge_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    if (!dict1 || !dict2) return NULL;
    
    Dictionary *merged = create_dictionary(dict1->size + dict2->size);
    if (!merged) return NULL;
    
    for (size_t i = 0; i < dict1->size; i++) {
        if (!add_to_dictionary(merged, dict1->pairs[i].key, dict1->pairs[i].value)) {
            free_dictionary(merged);
            return NULL;
        }
    }
    
    for (size_t i = 0; i < dict2->size; i++) {
        if (!add_to_dictionary(merged, dict2->pairs[i].key, dict2->pairs[i].value)) {
            free_dictionary(merged);
            return NULL;
        }
    }
    
    return merged;
}

int main(void) {
    Dictionary *dict1 = create_dictionary(2);
    if (!dict1) return 1;
    
    Dictionary *dict2 = create_dictionary(2);
    if (!dict2) {
        free_dictionary(dict1);
        return 1;
    }
    
    if (!add_to_dictionary(dict1, "key1", "value1") ||
        !add_to_dictionary(dict1, "key2", "value2") ||
        !add_to_dictionary(dict2, "key2", "new_value2") ||
        !add_to_dictionary(dict2, "key3", "value3")) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    Dictionary *merged = merge_dictionaries(dict1, dict2);
    if (!merged) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    for (size_t i = 0; i < merged->size; i++) {
        printf("%s: %s\n", merged->pairs[i].key, merged->pairs[i].value);
    }
    
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);
    
    return 0;
}
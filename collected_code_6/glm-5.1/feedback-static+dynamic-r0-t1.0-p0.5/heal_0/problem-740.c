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
} Dictionary;

Dictionary* create_dictionary(size_t size) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->pairs = (KeyValuePair*)malloc(size * sizeof(KeyValuePair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }
    dict->size = size;
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

Dictionary* tuple_to_dict(const char **tuple, size_t tuple_size) {
    if (!tuple || tuple_size == 0 || tuple_size % 2 != 0) return NULL;
    
    size_t dict_size = tuple_size / 2;
    Dictionary *dict = create_dictionary(dict_size);
    if (!dict) return NULL;
    
    for (size_t i = 0; i < dict_size; i++) {
        const char *key = tuple[i * 2];
        const char *value = tuple[i * 2 + 1];
        
        if (!key || !value) {
            free_dictionary(dict);
            return NULL;
        }
        
        dict->pairs[i].key = strdup(key);
        dict->pairs[i].value = strdup(value);
        
        if (!dict->pairs[i].key || !dict->pairs[i].value) {
            free_dictionary(dict);
            return NULL;
        }
    }
    
    return dict;
}

int main() {
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "Wonderland"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    
    Dictionary *dict = tuple_to_dict(tuple, tuple_size);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }
    
    free_dictionary(dict);
    return 0;
}
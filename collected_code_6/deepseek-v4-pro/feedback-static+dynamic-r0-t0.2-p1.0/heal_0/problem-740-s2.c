#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

Dictionary tuple_to_dict(char **tuple, size_t tuple_size) {
    Dictionary dict;
    dict.count = tuple_size / 2;
    dict.pairs = (KeyValuePair *)malloc(dict.count * sizeof(KeyValuePair));
    
    if (dict.pairs == NULL) {
        dict.count = 0;
        return dict;
    }
    
    for (size_t i = 0; i < dict.count; i++) {
        dict.pairs[i].key = (char *)malloc(strlen(tuple[i * 2]) + 1);
        dict.pairs[i].value = (char *)malloc(strlen(tuple[i * 2 + 1]) + 1);
        
        if (dict.pairs[i].key == NULL || dict.pairs[i].value == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict.pairs[j].key);
                free(dict.pairs[j].value);
            }
            free(dict.pairs);
            dict.pairs = NULL;
            dict.count = 0;
            return dict;
        }
        
        strcpy(dict.pairs[i].key, tuple[i * 2]);
        strcpy(dict.pairs[i].value, tuple[i * 2 + 1]);
    }
    
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict->pairs != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
        dict->pairs = NULL;
        dict->count = 0;
    }
}

int main(void) {
    char *tuple[] = {"name", "John", "age", "30", "city", "New York"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    
    Dictionary dict = tuple_to_dict(tuple, tuple_size);
    
    if (dict.pairs == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }
    
    for (size_t i = 0; i < dict.count; i++) {
        printf("%s: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }
    
    free_dictionary(&dict);
    
    return 0;
}
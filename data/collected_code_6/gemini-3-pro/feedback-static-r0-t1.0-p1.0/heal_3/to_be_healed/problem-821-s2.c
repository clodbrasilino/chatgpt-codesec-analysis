#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char* duplicate_string(const char *src) {
    if (!src) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src) + 1;
    char *dest = (char*)malloc(len);
    if (dest) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len);
    }
    return dest;
}

Dictionary* create_dictionary(size_t capacity) {
    if (capacity == 0) return NULL;
    
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->entries = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict) {
        if (dict->entries) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                free(dict->entries[i].value);
            }
            free(dict->entries);
        }
        free(dict);
    }
}

int add_entry(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = duplicate_string(value);
            if (!new_value) return 0;
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 1;
        }
    }
    
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        if (new_capacity < dict->capacity) return 0;
        
        KeyValuePair *new_entries = (KeyValuePair*)realloc(dict->entries, new_capacity * sizeof(KeyValuePair));
        if (!new_entries) return 0;
        
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    
    char *new_key = duplicate_string(key);
    char *new_val = duplicate_string(value);
    
    if (!new_key || !new_val) {
        free(new_key);
        free(new_val);
        return 0;
    }
    
    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_val;
    dict->size++;
    
    return 1;
}

Dictionary* merge_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    if (!dict1 && !dict2) return NULL;
    
    size_t new_capacity = (dict1 ? dict1->size : 0) + (dict2 ? dict2->size : 0);
    if (new_capacity == 0) new_capacity = 1;
    
    Dictionary *merged = create_dictionary(new_capacity);
    if (!merged) return NULL;
    
    if (dict1) {
        for (size_t i = 0; i < dict1->size; i++) {
            if (!add_entry(merged, dict1->entries[i].key, dict1->entries[i].value)) {
                free_dictionary(merged);
                return NULL;
            }
        }
    }
    
    if (dict2) {
        for (size_t i = 0; i < dict2->size; i++) {
            if (!add_entry(merged, dict2->entries[i].key, dict2->entries[i].value)) {
                free_dictionary(merged);
                return NULL;
            }
        }
    }
    
    return merged;
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
    }
}

int main(void) {
    Dictionary *dict1 = create_dictionary(2);
    if (!dict1) return 1;
    
    Dictionary *dict2 = create_dictionary(2);
    if (!dict2) {
        free_dictionary(dict1);
        return 1;
    }
    
    if (!add_entry(dict1, "key1", "value1") || !add_entry(dict1, "key2", "value2")) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    if (!add_entry(dict2, "key2", "new_value2") || !add_entry(dict2, "key3", "value3")) {
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
    
    print_dictionary(merged);
    
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);
    
    return 0;
}
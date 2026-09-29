#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 100
#define MAX_VAL_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VAL_LEN];
} KeyValuePair;

typedef struct {
    KeyValuePair *entries;
    size_t size;
    size_t capacity;
} Dictionary;

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
            free(dict->entries);
        }
        free(dict);
    }
}

int add_entry(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(dict->entries[i].value, value, MAX_VAL_LEN - 1);
            dict->entries[i].value[MAX_VAL_LEN - 1] = '\0';
            return 1;
        }
    }
    
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        KeyValuePair *new_entries = (KeyValuePair*)realloc(dict->entries, new_capacity * sizeof(KeyValuePair));
        if (!new_entries) return 0;
        
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->size].key, key, MAX_KEY_LEN - 1);
    dict->entries[dict->size].key[MAX_KEY_LEN - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->size].value, value, MAX_VAL_LEN - 1);
    dict->entries[dict->size].value[MAX_VAL_LEN - 1] = '\0';
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
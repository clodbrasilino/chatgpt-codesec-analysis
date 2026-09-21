#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *create_dictionary(void) {
    Dictionary *dict = malloc(sizeof(*dict));
    if (!dict) return NULL;
    
    dict->items = malloc(INITIAL_CAPACITY * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    
    free(dict->items);
    free(dict);
}

static int safe_string_copy(char **dest, const char *src, size_t src_len) {
    if (src_len >= SIZE_MAX) return 0;
    
    /* Possible weaknesses found:
     *  alloc_size is assigned 'src_len+1' here.
     */
    size_t alloc_size = src_len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<src_len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<src_len' is always false
     */
    if (alloc_size < src_len) return 0;
    
    *dest = malloc(alloc_size);
    if (!*dest) return 0;
    
    if (src_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*dest, src, src_len);
    }
    (*dest)[src_len] = '\0';
    return 1;
}

int dictionary_add(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    size_t key_len = strnlen(key, dict->capacity > 0 ? dict->capacity * 8 : 256);
    size_t value_len = strnlen(value, dict->capacity > 0 ? dict->capacity * 8 : 256);
    
    if (key_len >= (dict->capacity > 0 ? dict->capacity * 8 : 256)) return 0;
    if (value_len >= (dict->capacity > 0 ? dict->capacity * 8 : 256)) return 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            char *new_value = NULL;
            if (!safe_string_copy(&new_value, value, value_len)) {
                return 0;
            }
            free(dict->items[i].value);
            dict->items[i].value = new_value;
            return 1;
        }
    }
    
    if (dict->size == dict->capacity) {
        if (dict->capacity > SIZE_MAX / 2) return 0;
        size_t new_capacity = dict->capacity * 2;
        
        if (new_capacity > SIZE_MAX / sizeof(DictItem)) return 0;
        
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (!new_items) return 0;
        
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    
    char *key_copy = NULL;
    char *value_copy = NULL;
    
    if (!safe_string_copy(&key_copy, key, key_len)) {
        return 0;
    }
    
    if (!safe_string_copy(&value_copy, value, value_len)) {
        free(key_copy);
        return 0;
    }
    
    dict->items[dict->size].key = key_copy;
    dict->items[dict->size].value = value_copy;
    dict->size++;
    
    return 1;
}

void dictionary_remove_empty(Dictionary *dict) {
    if (!dict) return;
    
    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < dict->size; read_index++) {
        if (dict->items[read_index].value != NULL && dict->items[read_index].value[0] == '\0') {
            free(dict->items[read_index].key);
            free(dict->items[read_index].value);
        } else {
            if (write_index != read_index) {
                dict->items[write_index] = dict->items[read_index];
            }
            write_index++;
        }
    }
    
    dict->size = write_index;
}

void dictionary_print(const Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }
}

int main(void) {
    Dictionary *dict = create_dictionary();
    if (!dict) return EXIT_FAILURE;
    
    printf("Original dictionary:\n");
    dictionary_add(dict, "key1", "value1");
    dictionary_add(dict, "key2", "");
    dictionary_add(dict, "key3", "value3");
    dictionary_add(dict, "key4", "");
    dictionary_add(dict, "key5", "value5");
    dictionary_print(dict);
    
    dictionary_remove_empty(dict);
    
    printf("\nAfter removing empty items:\n");
    dictionary_print(dict);
    
    destroy_dictionary(dict);
    
    return EXIT_SUCCESS;
}
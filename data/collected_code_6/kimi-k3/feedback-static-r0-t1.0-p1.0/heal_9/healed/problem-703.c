#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 100
#define INITIAL_CAPACITY 16

typedef struct {
    char *key;
    char *value;
    bool is_occupied;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t count;
} Dictionary;

static char *safe_strdup(const char *src, size_t max_len) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strnlen(src, max_len);
    if (len == 0 || len >= max_len) {
        return NULL;
    }
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }
    strncpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

bool dictionary_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL) {
        return false;
    }
    if (capacity == 0) {
        capacity = INITIAL_CAPACITY;
    }
    
    dict->entries = calloc(capacity, sizeof(Entry));
    if (dict->entries == NULL) {
        return false;
    }
    
    dict->capacity = capacity;
    dict->count = 0;
    return true;
}

void dictionary_free(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->capacity; i++) {
                if (dict->entries[i].is_occupied) {
                    free(dict->entries[i].key);
                    free(dict->entries[i].value);
                }
            }
            free(dict->entries);
        }
        dict->entries = NULL;
        dict->capacity = 0;
        dict->count = 0;
    }
}

bool dictionary_contains_key(const Dictionary *dict, const char *key) {
    if (dict == NULL || dict->entries == NULL || key == NULL) {
        return false;
    }
    
    size_t key_len = strnlen(key, MAX_KEY_LENGTH);
    if (key_len == 0 || key_len >= MAX_KEY_LENGTH) {
        return false;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        if (dict->entries[i].is_occupied) {
            if (strncmp(dict->entries[i].key, key, MAX_KEY_LENGTH) == 0) {
                return true;
            }
        }
    }
    
    return false;
}

bool dictionary_insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || dict->entries == NULL || key == NULL || value == NULL) {
        return false;
    }
    
    size_t key_len = strnlen(key, MAX_KEY_LENGTH);
    size_t value_len = strnlen(value, MAX_VALUE_LENGTH);
    
    if (key_len == 0 || key_len >= MAX_KEY_LENGTH || value_len >= MAX_VALUE_LENGTH) {
        return false;
    }
    
    if (dict->count >= dict->capacity) {
        return false;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        if (!dict->entries[i].is_occupied) {
            char *key_copy = safe_strdup(key, MAX_KEY_LENGTH);
            if (key_copy == NULL) {
                return false;
            }
            char *value_copy = safe_strdup(value, MAX_VALUE_LENGTH);
            if (value_copy == NULL) {
                free(key_copy);
                return false;
            }
            dict->entries[i].key = key_copy;
            dict->entries[i].value = value_copy;
            dict->entries[i].is_occupied = true;
            dict->count++;
            return true;
        }
    }
    
    return false;
}

int main(void) {
    Dictionary dict;
    
    if (!dictionary_init(&dict, 0)) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    if (!dictionary_insert(&dict, "name", "Alice")) {
        fprintf(stderr, "Failed to insert key\n");
        dictionary_free(&dict);
        return EXIT_FAILURE;
    }
    
    if (!dictionary_insert(&dict, "age", "30")) {
        fprintf(stderr, "Failed to insert key\n");
        dictionary_free(&dict);
        return EXIT_FAILURE;
    }
    
    if (!dictionary_insert(&dict, "city", "New York")) {
        fprintf(stderr, "Failed to insert key\n");
        dictionary_free(&dict);
        return EXIT_FAILURE;
    }
    
    const char *test_key = "age";
    if (dictionary_contains_key(&dict, test_key)) {
        printf("Key '%s' is present in the dictionary\n", test_key);
    } else {
        printf("Key '%s' is not present in the dictionary\n", test_key);
    }
    
    test_key = "country";
    if (dictionary_contains_key(&dict, test_key)) {
        printf("Key '%s' is present in the dictionary\n", test_key);
    } else {
        printf("Key '%s' is not present in the dictionary\n", test_key);
    }
    
    dictionary_free(&dict);
    return EXIT_SUCCESS;
}
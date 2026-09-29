#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue **buckets;
    size_t size;
} Dictionary;

static unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Dictionary *create_dictionary(size_t size) {
    if (size == 0) {
        return NULL;
    }
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = size;
    dict->buckets = (KeyValue **)calloc(size, sizeof(KeyValue *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        KeyValue *current = dict->buckets[i];
        while (current != NULL) {
            KeyValue *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    
    size_t key_len = strnlen(key, 1024);
    if (key_len == 1024) {
        return -1;
    }
    
    unsigned long index = hash_function(key) % dict->size;
    KeyValue *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }
    
    if (key_len >= SIZE_MAX) {
        free(new_pair);
        return -1;
    }
    
    size_t alloc_size = key_len + 1;
    if (alloc_size < key_len) {
        free(new_pair);
        return -1;
    }
    
    new_pair->key = (char *)malloc(alloc_size);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    
    memcpy(new_pair->key, key, key_len);
    new_pair->key[key_len] = '\0';
    new_pair->value = value;
    new_pair->next = dict->buckets[index];
    dict->buckets[index] = new_pair;
    return 0;
}

int dictionary_get_by_index(Dictionary *dict, size_t index, char **key, int *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    size_t current_index = 0;
    for (size_t i = 0; i < dict->size; i++) {
        KeyValue *current = dict->buckets[i];
        while (current != NULL) {
            if (current_index == index) {
                *key = current->key;
                *value = current->value;
                return 0;
            }
            current_index++;
            current = current->next;
        }
    }
    return -1;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (dict == NULL) {
        return 1;
    }

    dictionary_insert(dict, "apple", 100);
    dictionary_insert(dict, "banana", 200);
    dictionary_insert(dict, "cherry", 300);

    char *key = NULL;
    int value = 0;

    if (dictionary_get_by_index(dict, 0, &key, &value) == 0) {
        printf("Index 0: %s = %d\n", key, value);
    }

    if (dictionary_get_by_index(dict, 1, &key, &value) == 0) {
        printf("Index 1: %s = %d\n", key, value);
    }

    if (dictionary_get_by_index(dict, 2, &key, &value) == 0) {
        printf("Index 2: %s = %d\n", key, value);
    }

    if (dictionary_get_by_index(dict, 3, &key, &value) != 0) {
        printf("Index 3 not found\n");
    }

    destroy_dictionary(dict);
    return 0;
}
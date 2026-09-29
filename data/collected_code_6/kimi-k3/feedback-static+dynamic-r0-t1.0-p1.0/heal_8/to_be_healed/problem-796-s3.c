#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 50

typedef struct {
    char *key;
    int value;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

int initDictionary(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    
    dict->items = (DictionaryItem *)calloc(capacity, sizeof(DictionaryItem));
    if (dict->items == NULL) {
        return -1;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

void freeDictionary(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->items != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->items[i].key);
                dict->items[i].key = NULL;
            }
            free(dict->items);
            dict->items = NULL;
        }
        dict->size = 0;
        dict->capacity = 0;
    }
}

int addItem(Dictionary *dict, const char *key, int value) {
    size_t key_len;
    
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    
    key_len = strnlen(key, MAX_KEY_LENGTH);
    if (key_len >= MAX_KEY_LENGTH) {
        return -1;
    }
    
    dict->items[dict->size].key = (char *)malloc(key_len + 1);
    if (dict->items[dict->size].key == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->items[dict->size].key, key, key_len);
    dict->items[dict->size].key[key_len] = '\0';
    dict->items[dict->size].value = value;
    dict->size++;
    
    return 0;
}

int sumDictionaryValues(const Dictionary *dict, long *result) {
    if (dict == NULL || result == NULL) {
        return -1;
    }
    
    *result = 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        *result += dict->items[i].value;
    }
    
    return 0;
}

int main(void) {
    Dictionary dict;
    long sum = 0;
    
    if (initDictionary(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    if (addItem(&dict, "apple", 10) != 0 ||
        addItem(&dict, "banana", 20) != 0 ||
        addItem(&dict, "orange", 30) != 0 ||
        addItem(&dict, "grape", 15) != 0) {
        fprintf(stderr, "Failed to add items\n");
        freeDictionary(&dict);
        return EXIT_FAILURE;
    }
    
    if (sumDictionaryValues(&dict, &sum) != 0) {
        fprintf(stderr, "Failed to calculate sum\n");
        freeDictionary(&dict);
        return EXIT_FAILURE;
    }
    
    printf("Sum of all items: %ld\n", sum);
    
    freeDictionary(&dict);
    
    return EXIT_SUCCESS;
}
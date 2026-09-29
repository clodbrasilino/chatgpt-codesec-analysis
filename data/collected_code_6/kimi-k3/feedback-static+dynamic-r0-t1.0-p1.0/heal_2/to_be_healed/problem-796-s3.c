#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
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
    if (dict != NULL && dict->items != NULL) {
        free(dict->items);
        dict->items = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int addItem(Dictionary *dict, const char *key, int value) {
    size_t key_len;
    
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    key_len = strlen(key);
    if (key_len >= MAX_KEY_LENGTH) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dict->items[dict->size].key, key);
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
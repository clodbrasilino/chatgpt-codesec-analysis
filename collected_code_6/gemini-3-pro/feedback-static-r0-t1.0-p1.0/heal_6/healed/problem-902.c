#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_KEY_LEN 1024

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair items[MAX_KEYS];
    int size;
} Dictionary;

void initDictionary(Dictionary* dict) {
    if (dict == NULL) return;
    dict->size = 0;
}

void freeDictionary(Dictionary* dict) {
    if (dict == NULL) return;
    for (int i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        dict->items[i].key = NULL;
    }
    dict->size = 0;
}

int addOrUpdate(Dictionary* dict, const char* key, int value) {
    if (dict == NULL || key == NULL) return -1;

    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value += value;
            return 0;
        }
    }

    if (dict->size >= MAX_KEYS) return -1;
    
    size_t key_len = 0;
    while (key[key_len] != '\0' && key_len < MAX_KEY_LEN) {
        key_len++;
    }
    if (key_len == MAX_KEY_LEN) return -1;

    dict->items[dict->size].key = (char *)malloc(key_len + 1);
    if (dict->items[dict->size].key == NULL) return -1;

    for (size_t i = 0; i < key_len; i++) {
        dict->items[dict->size].key[i] = key[i];
    }
    dict->items[dict->size].key[key_len] = '\0';
    
    dict->items[dict->size].value = value;
    dict->size++;

    return 0;
}

int combineDictionaries(const Dictionary* dict1, const Dictionary* dict2, Dictionary* result) {
    if (dict1 == NULL || dict2 == NULL || result == NULL) return -1;

    initDictionary(result);

    for (int i = 0; i < dict1->size; i++) {
        if (addOrUpdate(result, dict1->items[i].key, dict1->items[i].value) != 0) {
            return -1;
        }
    }

    for (int i = 0; i < dict2->size; i++) {
        if (addOrUpdate(result, dict2->items[i].key, dict2->items[i].value) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void) {
    Dictionary dict1, dict2, result;
    int status = 0;

    initDictionary(&dict1);
    initDictionary(&dict2);
    initDictionary(&result);

    if (addOrUpdate(&dict1, "apple", 10) != 0) { status = 1; goto cleanup; }
    if (addOrUpdate(&dict1, "banana", 20) != 0) { status = 1; goto cleanup; }
    if (addOrUpdate(&dict1, "cherry", 30) != 0) { status = 1; goto cleanup; }

    if (addOrUpdate(&dict2, "banana", 15) != 0) { status = 1; goto cleanup; }
    if (addOrUpdate(&dict2, "cherry", 5) != 0) { status = 1; goto cleanup; }
    if (addOrUpdate(&dict2, "date", 40) != 0) { status = 1; goto cleanup; }

    if (combineDictionaries(&dict1, &dict2, &result) == 0) {
        for (int i = 0; i < result.size; i++) {
            printf("%s: %d\n", result.items[i].key, result.items[i].value);
        }
    } else {
        printf("Error combining dictionaries.\n");
        status = 1;
    }

cleanup:
    freeDictionary(&dict1);
    freeDictionary(&dict2);
    freeDictionary(&result);

    return status;
}
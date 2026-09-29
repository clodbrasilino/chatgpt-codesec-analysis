#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_KEY_LEN 50

typedef struct {
    char key[MAX_KEY_LEN];
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

int addOrUpdate(Dictionary* dict, const char* key, int value) {
    if (dict == NULL || key == NULL) return -1;

    for (int i = 0; i < dict->size; i++) {
        if (strncmp(dict->items[i].key, key, MAX_KEY_LEN) == 0) {
            dict->items[i].value += value;
            return 0;
        }
    }

    if (dict->size >= MAX_KEYS) return -1;

    strncpy(dict->items[dict->size].key, key, MAX_KEY_LEN - 1);
    dict->items[dict->size].key[MAX_KEY_LEN - 1] = '\0';
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

    initDictionary(&dict1);
    initDictionary(&dict2);
    initDictionary(&result);

    addOrUpdate(&dict1, "apple", 10);
    addOrUpdate(&dict1, "banana", 20);
    addOrUpdate(&dict1, "cherry", 30);

    addOrUpdate(&dict2, "banana", 15);
    addOrUpdate(&dict2, "cherry", 5);
    addOrUpdate(&dict2, "date", 40);

    if (combineDictionaries(&dict1, &dict2, &result) == 0) {
        for (int i = 0; i < result.size; i++) {
            printf("%s: %d\n", result.items[i].key, result.items[i].value);
        }
    } else {
        printf("Error combining dictionaries.\n");
        return 1;
    }

    return 0;
}
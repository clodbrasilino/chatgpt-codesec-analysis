#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_KEY_LEN 50

typedef struct {
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_KEYS];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 0) {
        return false;
    }
    
    int first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;
    
    if (dict.size < MAX_KEYS) {
        strncpy(dict.entries[dict.size].key, "a", MAX_KEY_LEN - 1);
        dict.entries[dict.size].key[MAX_KEY_LEN - 1] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (dict.size < MAX_KEYS) {
        strncpy(dict.entries[dict.size].key, "b", MAX_KEY_LEN - 1);
        dict.entries[dict.size].key[MAX_KEY_LEN - 1] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (dict.size < MAX_KEYS) {
        strncpy(dict.entries[dict.size].key, "c", MAX_KEY_LEN - 1);
        dict.entries[dict.size].key[MAX_KEY_LEN - 1] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }
    
    if (dict.size > 2) {
        dict.entries[2].value = 10;
    }
    
    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_SIZE 100
#define KEY_SIZE 50

typedef struct {
    char key[KEY_SIZE];
    int value;
    int is_used;
} Entry;

typedef struct {
    Entry entries[DICT_SIZE];
    int count;
} Dictionary;

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->count = 0;
    for (int i = 0; i < DICT_SIZE; i++) {
        dict->entries[i].is_used = 0;
        dict->entries[i].value = 0;
        dict->entries[i].key[0] = '\0';
    }
}

int dict_is_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    return (dict->count == 0) ? 1 : 0;
}

int dict_set(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->count >= DICT_SIZE) {
        return -1;
    }
    
    for (int i = 0; i < DICT_SIZE; i++) {
        if (dict->entries[i].is_used && strncmp(dict->entries[i].key, key, KEY_SIZE - 1) == 0) {
            dict->entries[i].value = value;
            return 0;
        }
    }
    
    for (int i = 0; i < DICT_SIZE; i++) {
        if (!dict->entries[i].is_used) {
            strncpy(dict->entries[i].key, key, KEY_SIZE - 1);
            dict->entries[i].key[KEY_SIZE - 1] = '\0';
            dict->entries[i].value = value;
            dict->entries[i].is_used = 1;
            dict->count++;
            return 0;
        }
    }
    
    return -1;
}

int main(void) {
    Dictionary dict;
    int result;

    dict_init(&dict);

    result = dict_is_empty(&dict);
    if (result == 1) {
        printf("Dictionary is empty\n");
    } else if (result == 0) {
        printf("Dictionary is not empty\n");
    } else {
        printf("Invalid dictionary pointer\n");
    }

    dict_set(&dict, "test", 42);

    result = dict_is_empty(&dict);
    if (result == 1) {
        printf("Dictionary is empty\n");
    } else if (result == 0) {
        printf("Dictionary is not empty\n");
    } else {
        printf("Invalid dictionary pointer\n");
    }

    return 0;
}
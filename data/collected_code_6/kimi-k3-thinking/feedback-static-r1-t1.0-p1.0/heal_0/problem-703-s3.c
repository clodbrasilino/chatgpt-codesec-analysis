#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 100
#define KEY_SIZE 64
#define VALUE_SIZE 128

typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
    int occupied;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_ENTRIES];
    size_t count;
} Dictionary;

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->count = 0;
    for (size_t i = 0; i < MAX_ENTRIES; i++) {
        dict->entries[i].occupied = 0;
        dict->entries[i].key[0] = '\0';
        dict->entries[i].value[0] = '\0';
    }
}

bool dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= MAX_ENTRIES) {
        return false;
    }
    if (strlen(key) >= KEY_SIZE || strlen(value) >= VALUE_SIZE) {
        return false;
    }
    DictEntry *entry = &dict->entries[dict->count];
    strncpy(entry->key, key, KEY_SIZE - 1);
    entry->key[KEY_SIZE - 1] = '\0';
    strncpy(entry->value, value, VALUE_SIZE - 1);
    entry->value[VALUE_SIZE - 1] = '\0';
    entry->occupied = 1;
    dict->count++;
    return true;
}

bool dict_contains_key(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return false;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].occupied && strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);

    if (!dict_add(&dict, "apple", "fruit")) {
        fprintf(stderr, "Error: failed to add key\n");
        return 1;
    }
    if (!dict_add(&dict, "carrot", "vegetable")) {
        fprintf(stderr, "Error: failed to add key\n");
        return 1;
    }
    if (!dict_add(&dict, "chicken", "meat")) {
        fprintf(stderr, "Error: failed to add key\n");
        return 1;
    }

    const char *keys_to_check[] = {"apple", "banana", "chicken", "grape"};
    size_t num_keys = sizeof(keys_to_check) / sizeof(keys_to_check[0]);

    for (size_t i = 0; i < num_keys; i++) {
        if (dict_contains_key(&dict, keys_to_check[i])) {
            printf("Key \"%s\" is present in the dictionary.\n", keys_to_check[i]);
        } else {
            printf("Key \"%s\" is NOT present in the dictionary.\n", keys_to_check[i]);
        }
    }

    return 0;
}
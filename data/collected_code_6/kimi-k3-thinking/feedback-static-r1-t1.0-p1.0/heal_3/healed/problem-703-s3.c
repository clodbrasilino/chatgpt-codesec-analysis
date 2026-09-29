#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 100
#define MAX_STRING_LEN 1024

typedef struct {
    char *key;
    char *value;
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
        dict->entries[i].key = NULL;
        dict->entries[i].value = NULL;
    }
}

bool dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= MAX_ENTRIES) {
        return false;
    }

    size_t key_len = strnlen(key, MAX_STRING_LEN);
    size_t value_len = strnlen(value, MAX_STRING_LEN);

    if (key_len == 0 || key_len >= MAX_STRING_LEN) {
        return false;
    }
    if (value_len >= MAX_STRING_LEN) {
        return false;
    }

    DictEntry *entry = &dict->entries[dict->count];

    entry->key = malloc(key_len + 1);
    if (entry->key == NULL) {
        return false;
    }
    entry->value = malloc(value_len + 1);
    if (entry->value == NULL) {
        free(entry->key);
        entry->key = NULL;
        return false;
    }

    snprintf(entry->key, key_len + 1, "%s", key);
    snprintf(entry->value, value_len + 1, "%s", value);

    entry->occupied = 1;
    dict->count++;
    return true;
}

bool dict_contains_key(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return false;
    }
    if (strnlen(key, MAX_STRING_LEN) >= MAX_STRING_LEN) {
        return false;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].occupied &&
            dict->entries[i].key != NULL &&
            strncmp(dict->entries[i].key, key, MAX_STRING_LEN) == 0) {
            return true;
        }
    }
    return false;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].occupied) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
            dict->entries[i].key = NULL;
            dict->entries[i].value = NULL;
            dict->entries[i].occupied = 0;
        }
    }
    dict->count = 0;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);

    if (!dict_add(&dict, "apple", "fruit")) {
        fprintf(stderr, "Error: failed to add key\n");
        dict_free(&dict);
        return 1;
    }
    if (!dict_add(&dict, "carrot", "vegetable")) {
        fprintf(stderr, "Error: failed to add key\n");
        dict_free(&dict);
        return 1;
    }
    if (!dict_add(&dict, "chicken", "meat")) {
        fprintf(stderr, "Error: failed to add key\n");
        dict_free(&dict);
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

    dict_free(&dict);
    return 0;
}
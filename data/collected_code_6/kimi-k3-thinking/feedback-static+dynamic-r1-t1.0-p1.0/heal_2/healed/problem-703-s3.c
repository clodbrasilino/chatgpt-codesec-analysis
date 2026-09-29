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

static size_t bounded_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static bool safe_copy(char *dest, size_t dest_size, const char *src) {
    int written;
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    written = snprintf(dest, dest_size, "%s", src);
    if (written < 0 || (size_t)written >= dest_size) {
        dest[0] = '\0';
        return false;
    }
    return true;
}

void dict_init(Dictionary *dict) {
    size_t i;
    if (dict == NULL) {
        return;
    }
    dict->count = 0;
    for (i = 0; i < MAX_ENTRIES; i++) {
        dict->entries[i].occupied = 0;
        dict->entries[i].key[0] = '\0';
        dict->entries[i].value[0] = '\0';
    }
}

bool dict_contains_key(const Dictionary *dict, const char *key) {
    size_t i;
    if (dict == NULL || key == NULL) {
        return false;
    }
    if (bounded_strlen(key, KEY_SIZE) >= KEY_SIZE) {
        return false;
    }
    for (i = 0; i < dict->count; i++) {
        if (dict->entries[i].occupied &&
            strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

bool dict_add(Dictionary *dict, const char *key, const char *value) {
    DictEntry *entry;
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= MAX_ENTRIES) {
        return false;
    }
    if (bounded_strlen(key, KEY_SIZE) >= KEY_SIZE ||
        bounded_strlen(value, VALUE_SIZE) >= VALUE_SIZE) {
        return false;
    }
    if (dict_contains_key(dict, key)) {
        return false;
    }
    entry = &dict->entries[dict->count];
    if (!safe_copy(entry->key, sizeof(entry->key), key)) {
        return false;
    }
    if (!safe_copy(entry->value, sizeof(entry->value), value)) {
        entry->key[0] = '\0';
        return false;
    }
    entry->occupied = 1;
    dict->count++;
    return true;
}

int main(void) {
    Dictionary dict;
    const char *keys_to_check[] = {"apple", "banana", "chicken", "grape"};
    size_t num_keys = sizeof(keys_to_check) / sizeof(keys_to_check[0]);
    size_t i;

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

    for (i = 0; i < num_keys; i++) {
        if (dict_contains_key(&dict, keys_to_check[i])) {
            printf("Key \"%s\" is present in the dictionary.\n", keys_to_check[i]);
        } else {
            printf("Key \"%s\" is NOT present in the dictionary.\n", keys_to_check[i]);
        }
    }

    return 0;
}
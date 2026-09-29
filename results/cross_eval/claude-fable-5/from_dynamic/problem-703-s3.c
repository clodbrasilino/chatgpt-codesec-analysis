#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 10
#define MAX_KEY_LEN 32
#define MAX_VAL_LEN 32

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_ENTRIES];
    size_t count;
} Dictionary;

bool dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= MAX_ENTRIES) {
        return false;
    }
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VAL_LEN) {
        return false;
    }
    strncpy(dict->entries[dict->count].key, key, MAX_KEY_LEN - 1);
    dict->entries[dict->count].key[MAX_KEY_LEN - 1] = '\0';
    strncpy(dict->entries[dict->count].value, value, MAX_VAL_LEN - 1);
    dict->entries[dict->count].value[MAX_VAL_LEN - 1] = '\0';
    dict->count++;
    return true;
}

bool dict_contains_key(const Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL) {
        return false;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    Dictionary dict = { .count = 0 };

    if (!dict_add(&dict, "apple", "fruit")) {
        fprintf(stderr, "Failed to add entry\n");
        return 1;
    }
    if (!dict_add(&dict, "carrot", "vegetable")) {
        fprintf(stderr, "Failed to add entry\n");
        return 1;
    }
    if (!dict_add(&dict, "salmon", "fish")) {
        fprintf(stderr, "Failed to add entry\n");
        return 1;
    }

    const char *keys_to_check[] = { "apple", "banana", "salmon" };
    size_t num_keys = sizeof(keys_to_check) / sizeof(keys_to_check[0]);

    for (size_t i = 0; i < num_keys; i++) {
        if (dict_contains_key(&dict, keys_to_check[i])) {
            printf("Key '%s' is present in the dictionary.\n", keys_to_check[i]);
        } else {
            printf("Key '%s' is NOT present in the dictionary.\n", keys_to_check[i]);
        }
    }

    return 0;
}
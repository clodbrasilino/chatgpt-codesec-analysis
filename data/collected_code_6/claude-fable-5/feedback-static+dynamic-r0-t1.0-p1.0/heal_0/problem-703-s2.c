#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DICT_CAPACITY 16
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} DictEntry;

typedef struct {
    DictEntry entries[DICT_CAPACITY];
    size_t count;
} Dictionary;

void dict_init(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->count = 0;
    memset(dict->entries, 0, sizeof(dict->entries));
}

bool dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= DICT_CAPACITY) {
        return false;
    }
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VALUE_LEN) {
        return false;
    }

    strncpy(dict->entries[dict->count].key, key, MAX_KEY_LEN - 1);
    dict->entries[dict->count].key[MAX_KEY_LEN - 1] = '\0';
    strncpy(dict->entries[dict->count].value, value, MAX_VALUE_LEN - 1);
    dict->entries[dict->count].value[MAX_VALUE_LEN - 1] = '\0';
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
    Dictionary dict;
    dict_init(&dict);

    if (!dict_add(&dict, "apple", "fruit")) {
        fprintf(stderr, "Failed to add entry\n");
        return EXIT_FAILURE;
    }
    if (!dict_add(&dict, "carrot", "vegetable")) {
        fprintf(stderr, "Failed to add entry\n");
        return EXIT_FAILURE;
    }
    if (!dict_add(&dict, "salmon", "fish")) {
        fprintf(stderr, "Failed to add entry\n");
        return EXIT_FAILURE;
    }

    const char *keys_to_check[] = { "apple", "banana", "salmon", "onion" };
    size_t num_keys = sizeof(keys_to_check) / sizeof(keys_to_check[0]);

    for (size_t i = 0; i < num_keys; i++) {
        if (dict_contains_key(&dict, keys_to_check[i])) {
            if (printf("Key '%s' is present in the dictionary.\n", keys_to_check[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Key '%s' is not present in the dictionary.\n", keys_to_check[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}
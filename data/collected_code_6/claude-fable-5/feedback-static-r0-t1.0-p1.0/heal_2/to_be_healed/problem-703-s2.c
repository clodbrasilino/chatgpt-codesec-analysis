#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DICT_CAPACITY 16
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    size_t key_len = strnlen(key, MAX_KEY_LEN);
    size_t value_len = strnlen(value, MAX_VALUE_LEN);

    if (key_len >= MAX_KEY_LEN || value_len >= MAX_VALUE_LEN) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->count].key, key, key_len);
    dict->entries[dict->count].key[key_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->count].value, value, value_len);
    dict->entries[dict->count].value[value_len] = '\0';

    dict->count++;
    return true;
}

bool dict_contains_key(const Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0; i < dict->count; i++) {
        if (strncmp(dict->entries[i].key, key, MAX_KEY_LEN) == 0) {
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
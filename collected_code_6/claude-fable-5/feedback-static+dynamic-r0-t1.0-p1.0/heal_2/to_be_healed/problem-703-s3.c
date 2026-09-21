#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 10
#define MAX_KEY_LEN 32
#define MAX_VAL_LEN 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    size_t key_len = strnlen(key, MAX_KEY_LEN);
    size_t val_len = strnlen(value, MAX_VAL_LEN);

    if (key_len >= MAX_KEY_LEN || val_len >= MAX_VAL_LEN) {
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
    memcpy(dict->entries[dict->count].value, value, val_len);
    dict->entries[dict->count].value[val_len] = '\0';

    dict->count++;
    return true;
}

bool dict_contains_key(const Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL) {
        return false;
    }
    if (strnlen(key, MAX_KEY_LEN) >= MAX_KEY_LEN) {
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
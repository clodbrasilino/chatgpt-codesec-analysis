#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 10
#define MAX_KEY_LEN 32
#define MAX_VALUE_LEN 32

struct DictEntry {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LEN];
};

struct Dictionary {
    struct DictEntry entries[MAX_ENTRIES];
    size_t count;
};

static bool dict_add(struct Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->count >= MAX_ENTRIES) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VALUE_LEN) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->count].key, key, MAX_KEY_LEN - 1);
    dict->entries[dict->count].key[MAX_KEY_LEN - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->count].value, value, MAX_VALUE_LEN - 1);
    dict->entries[dict->count].value[MAX_VALUE_LEN - 1] = '\0';
    dict->count++;
    return true;
}

static bool dict_contains_key(const struct Dictionary *dict, const char *key)
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
    struct Dictionary dict = { .count = 0 };

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
            if (printf("Key '%s' is present in the dictionary.\n", keys_to_check[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("Key '%s' is not present in the dictionary.\n", keys_to_check[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}
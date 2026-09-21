#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_ENTRIES 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LENGTH];
} DictionaryEntry;

typedef struct {
    DictionaryEntry entries[MAX_ENTRIES];
    int count;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->count == 0) {
        return true;
    }

    const char *first_value = dict->entries[0].value;

    for (int i = 1; i < dict->count; i++) {
        if (strncmp(first_value, dict->entries[i].value, MAX_VALUE_LENGTH) != 0) {
            return false;
        }
    }

    return true;
}

static void set_entry(DictionaryEntry *entry, const char *key, const char *value) {
    if (entry == NULL || key == NULL || value == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(entry->key, key, MAX_KEY_LENGTH - 1);
    entry->key[MAX_KEY_LENGTH - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(entry->value, value, MAX_VALUE_LENGTH - 1);
    entry->value[MAX_VALUE_LENGTH - 1] = '\0';
}

int main(void) {
    Dictionary dict;
    dict.count = 0;

    set_entry(&dict.entries[dict.count++], "first", "apple");
    set_entry(&dict.entries[dict.count++], "second", "apple");
    set_entry(&dict.entries[dict.count++], "third", "apple");

    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }

    set_entry(&dict.entries[dict.count++], "fourth", "orange");

    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }

    return 0;
}
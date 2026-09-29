#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LENGTH];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 0) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (strcmp(first_value, dict->entries[i].value) != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;

    snprintf(dict.entries[dict.size].key, MAX_KEY_LENGTH, "%s", "a");
    snprintf(dict.entries[dict.size].value, MAX_VALUE_LENGTH, "%s", "same");
    dict.size++;

    snprintf(dict.entries[dict.size].key, MAX_KEY_LENGTH, "%s", "b");
    snprintf(dict.entries[dict.size].value, MAX_VALUE_LENGTH, "%s", "same");
    dict.size++;

    snprintf(dict.entries[dict.size].key, MAX_KEY_LENGTH, "%s", "c");
    snprintf(dict.entries[dict.size].value, MAX_VALUE_LENGTH, "%s", "same");
    dict.size++;

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    snprintf(dict.entries[dict.size].key, MAX_KEY_LENGTH, "%s", "d");
    snprintf(dict.entries[dict.size].value, MAX_VALUE_LENGTH, "%s", "different");
    dict.size++;

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}
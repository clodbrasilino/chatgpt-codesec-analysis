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

    if (dict->size > MAX_DICT_SIZE) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (strncmp(first_value, dict->entries[i].value, MAX_VALUE_LENGTH) != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    memset(&dict, 0, sizeof(dict));
    dict.size = 0;

    if (dict.size < MAX_DICT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].key, "a", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (dict.size < MAX_DICT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].key, "b", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (dict.size < MAX_DICT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].key, "c", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    if (dict.size < MAX_DICT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].key, "d", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(dict.entries[dict.size].value, "different", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_KEY_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_KEYS];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 0) {
        return false;
    }
    
    int first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;
    
    if (dict.size < MAX_KEYS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen("a");
        if (len >= MAX_KEY_LEN) {
            len = MAX_KEY_LEN - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict.entries[dict.size].key, "a", len);
        dict.entries[dict.size].key[len] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (dict.size < MAX_KEYS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen("b");
        if (len >= MAX_KEY_LEN) {
            len = MAX_KEY_LEN - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict.entries[dict.size].key, "b", len);
        dict.entries[dict.size].key[len] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (dict.size < MAX_KEYS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen("c");
        if (len >= MAX_KEY_LEN) {
            len = MAX_KEY_LEN - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict.entries[dict.size].key, "c", len);
        dict.entries[dict.size].key[len] = '\0';
        dict.entries[dict.size].value = 5;
        dict.size++;
    }
    
    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }
    
    if (dict.size > 2) {
        dict.entries[2].value = 10;
    }
    
    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }
    
    return 0;
}
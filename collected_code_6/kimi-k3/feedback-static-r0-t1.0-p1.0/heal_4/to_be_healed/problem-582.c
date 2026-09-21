#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define DICTIONARY_SIZE 100
#define MAX_KEY_SIZE 50
#define MAX_VALUE_SIZE 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_SIZE];
} Entry;

typedef struct {
    Entry entries[DICTIONARY_SIZE];
    size_t count;
} Dictionary;

static size_t safe_strnlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

void initDictionary(Dictionary *dict) {
    if (dict != NULL) {
        memset(dict, 0, sizeof(Dictionary));
    }
}

bool isEmpty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

int insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    if (dict->count >= DICTIONARY_SIZE) {
        return -1;
    }
    
    size_t key_len = safe_strnlen(key, MAX_KEY_SIZE);
    size_t value_len = safe_strnlen(value, MAX_VALUE_SIZE);
    
    if (key_len == 0 || key_len >= MAX_KEY_SIZE || value_len >= MAX_VALUE_SIZE) {
        return -1;
    }
    
    if (key_len + 1 > MAX_KEY_SIZE || value_len + 1 > MAX_VALUE_SIZE) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->count].key, key, MAX_KEY_SIZE - 1);
    dict->entries[dict->count].key[MAX_KEY_SIZE - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->count].value, value, MAX_VALUE_SIZE - 1);
    dict->entries[dict->count].value[MAX_VALUE_SIZE - 1] = '\0';
    
    dict->count++;
    return 0;
}

int main(void) {
    Dictionary dict;
    initDictionary(&dict);

    if (isEmpty(&dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    if (insert(&dict, "name", "John") != 0) {
        fprintf(stderr, "Failed to insert entry.\n");
        return EXIT_FAILURE;
    }

    if (isEmpty(&dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    return EXIT_SUCCESS;
}
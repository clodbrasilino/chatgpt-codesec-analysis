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

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static bool add_entry(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->size >= MAX_KEYS) {
        return false;
    }
    
    size_t key_len = safe_strlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }
    
    if (key_len >= sizeof(dict->entries[dict->size].key)) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->size].key, key, key_len);
    dict->entries[dict->size].key[key_len] = '\0';
    dict->entries[dict->size].value = value;
    dict->size++;
    
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;
    
    add_entry(&dict, "a", 5);
    add_entry(&dict, "b", 5);
    add_entry(&dict, "c", 5);
    
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
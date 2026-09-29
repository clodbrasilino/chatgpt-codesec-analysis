#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_KEY_LEN 50

typedef struct {
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
        key_len = MAX_KEY_LEN - 1;
    }
    
    size_t src_len = key_len;
    if (src_len > MAX_KEY_LEN - 1) {
        src_len = MAX_KEY_LEN - 1;
    }
    
    memcpy(dict->entries[dict->size].key, key, src_len);
    dict->entries[dict->size].key[src_len] = '\0';
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
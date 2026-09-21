#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define DICTIONARY_SIZE 100
#define MAX_KEY_SIZE 50
#define MAX_VALUE_SIZE 50

typedef struct {
    char *key;
    char *value;
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

static char *safe_strdup(const char *src, size_t max_len) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t src_len = safe_strnlen(src, max_len);
    if (src_len >= max_len) {
        return NULL;
    }
    
    char *dest = malloc(src_len + 1);
    if (dest == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < src_len; i++) {
        dest[i] = src[i];
    }
    dest[src_len] = '\0';
    
    return dest;
}

void initDictionary(Dictionary *dict) {
    if (dict != NULL) {
        dict->count = 0;
        for (size_t i = 0; i < DICTIONARY_SIZE; i++) {
            dict->entries[i].key = NULL;
            dict->entries[i].value = NULL;
        }
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
    
    char *new_key = safe_strdup(key, MAX_KEY_SIZE);
    if (new_key == NULL) {
        return -1;
    }
    
    char *new_value = safe_strdup(value, MAX_VALUE_SIZE);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }
    
    dict->entries[dict->count].key = new_key;
    dict->entries[dict->count].value = new_value;
    dict->count++;
    
    return 0;
}

void freeDictionary(Dictionary *dict) {
    if (dict != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
            dict->entries[i].key = NULL;
            dict->entries[i].value = NULL;
        }
        dict->count = 0;
    }
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

    freeDictionary(&dict);

    return EXIT_SUCCESS;
}
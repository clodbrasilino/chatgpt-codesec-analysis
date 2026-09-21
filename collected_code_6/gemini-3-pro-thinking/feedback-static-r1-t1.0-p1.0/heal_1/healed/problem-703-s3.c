#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t capacity;
    size_t count;
} Dictionary;

char *safe_strdup(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < MAX_STR_LEN && src[len] != '\0') {
        len++;
    }
    
    char *dst = malloc(len + 1);
    if (!dst) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    dst[len] = '\0';
    
    return dst;
}

Dictionary *create_dictionary(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->items = calloc(capacity, sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->capacity = capacity;
    dict->count = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

bool add_item(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->count >= dict->capacity) {
        return false;
    }
    
    char *key_copy = safe_strdup(key);
    if (!key_copy) {
        return false;
    }

    dict->items[dict->count].key = key_copy;
    dict->items[dict->count].value = value;
    dict->count++;
    return true;
}

bool key_exists(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return false;
    }
    
    for (size_t i = 0; i < dict->count; ++i) {
        if (strncmp(dict->items[i].key, key, MAX_STR_LEN) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return EXIT_FAILURE;
    }

    if (!add_item(dict, "apple", 1)) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }
    
    if (!add_item(dict, "banana", 2)) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }

    bool has_apple = key_exists(dict, "apple");
    bool has_orange = key_exists(dict, "orange");

    printf("apple: %s\n", has_apple ? "present" : "not present");
    printf("orange: %s\n", has_orange ? "present" : "not present");

    free_dictionary(dict);
    return EXIT_SUCCESS;
}
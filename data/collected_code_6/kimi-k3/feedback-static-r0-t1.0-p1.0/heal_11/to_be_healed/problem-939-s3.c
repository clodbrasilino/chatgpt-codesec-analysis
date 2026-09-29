#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 256
#define MAX_ENTRIES 100

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static int compare_entries(const void *a, const void *b) {
    const DictEntry *entry_a = (const DictEntry *)a;
    const DictEntry *entry_b = (const DictEntry *)b;
    
    if (entry_a->key == NULL && entry_b->key == NULL) {
        return 0;
    }
    if (entry_a->key == NULL) {
        return -1;
    }
    if (entry_b->key == NULL) {
        return 1;
    }
    
    return strcmp(entry_a->key, entry_b->key);
}

static char *safe_strdup(const char *src, size_t max_len) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(src, max_len);
    if (len == 0 || len >= max_len) {
        return NULL;
    }
    
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dst, src, len);
    dst[len] = '\0';
    
    return dst;
}

int dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    
    dict->entries = calloc(MAX_ENTRIES, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    
    dict->size = 0;
    dict->capacity = MAX_ENTRIES;
    
    return 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    if (dict->size >= dict->capacity) {
        return -1;
    }
    
    size_t key_len = strnlen(key, MAX_KEY_LEN);
    size_t value_len = strnlen(value, MAX_VALUE_LEN);
    
    if (key_len == 0 || key_len >= MAX_KEY_LEN || value_len >= MAX_VALUE_LEN) {
        return -1;
    }
    
    char *key_copy = safe_strdup(key, MAX_KEY_LEN);
    if (key_copy == NULL) {
        return -1;
    }
    
    char *value_copy = safe_strdup(value, MAX_VALUE_LEN);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    
    return 0;
}

int dict_sort(Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    
    if (dict->size == 0) {
        return 0;
    }
    
    qsort(dict->entries, dict->size, sizeof(DictEntry), compare_entries);
    
    return 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->entries[i].key != NULL && dict->entries[i].value != NULL) {
            printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
        }
    }
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    
    dict->size = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict;
    
    if (dict_init(&dict) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    if (dict_add(&dict, "zebra", "animal") != 0 ||
        dict_add(&dict, "apple", "fruit") != 0 ||
        dict_add(&dict, "banana", "yellow") != 0 ||
        dict_add(&dict, "cherry", "red") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    
    printf("Before sorting:\n");
    dict_print(&dict);
    
    if (dict_sort(&dict) != 0) {
        fprintf(stderr, "Failed to sort dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    
    printf("\nAfter sorting:\n");
    dict_print(&dict);
    
    dict_free(&dict);
    
    return EXIT_SUCCESS;
}
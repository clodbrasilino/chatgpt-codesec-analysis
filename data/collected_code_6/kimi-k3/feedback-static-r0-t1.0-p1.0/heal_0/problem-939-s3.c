#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 256
#define MAX_ENTRIES 100

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_ENTRIES];
    size_t size;
} Dictionary;

int compare_entries(const void *a, const void *b) {
    const DictEntry *entry_a = (const DictEntry *)a;
    const DictEntry *entry_b = (const DictEntry *)b;
    return strcmp(entry_a->key, entry_b->key);
}

int dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    dict->size = 0;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= MAX_ENTRIES) {
        return -1;
    }
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VALUE_LEN) {
        return -1;
    }
    
    strncpy(dict->entries[dict->size].key, key, MAX_KEY_LEN - 1);
    dict->entries[dict->size].key[MAX_KEY_LEN - 1] = '\0';
    strncpy(dict->entries[dict->size].value, value, MAX_VALUE_LEN - 1);
    dict->entries[dict->size].value[MAX_VALUE_LEN - 1] = '\0';
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
        printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
    }
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
        return EXIT_FAILURE;
    }
    
    printf("Before sorting:\n");
    dict_print(&dict);
    
    if (dict_sort(&dict) != 0) {
        fprintf(stderr, "Failed to sort dictionary\n");
        return EXIT_FAILURE;
    }
    
    printf("\nAfter sorting:\n");
    dict_print(&dict);
    
    return EXIT_SUCCESS;
}
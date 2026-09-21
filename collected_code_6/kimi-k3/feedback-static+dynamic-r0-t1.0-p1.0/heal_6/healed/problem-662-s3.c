#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#define DICT_KEY_MAX 64
#define DICT_INITIAL_CAPACITY 16
#define DICT_MAX_CAPACITY 1048576

typedef struct {
    char key[DICT_KEY_MAX];
    int *values;
    size_t size;
    size_t capacity;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

static bool safe_multiply_size(size_t a, size_t b, size_t *result) {
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }
    if (a > SIZE_MAX / b) {
        return false;
    }
    *result = a * b;
    return true;
}

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0 || capacity > DICT_MAX_CAPACITY) {
        return -1;
    }
    
    size_t alloc_size;
    if (!safe_multiply_size(capacity, sizeof(DictEntry), &alloc_size)) {
        return -1;
    }
    
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

int dict_add_entry(Dictionary *dict, const char *key, const int *values, size_t num_values) {
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    if (num_values > 0 && values == NULL) {
        return -1;
    }
    if (num_values > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    DictEntry *entry = &dict->entries[dict->size];
    
    size_t key_len = strnlen(key, DICT_KEY_MAX - 1);
    if (key_len == 0 || key_len >= DICT_KEY_MAX) {
        return -1;
    }
    
    size_t copy_len = key_len < DICT_KEY_MAX - 1 ? key_len : DICT_KEY_MAX - 1;
    if (copy_len >= DICT_KEY_MAX) {
        return -1;
    }
    memcpy(entry->key, key, copy_len);
    entry->key[copy_len] = '\0';
    
    entry->capacity = num_values > 0 ? num_values : 1;
    
    size_t alloc_size;
    if (!safe_multiply_size(entry->capacity, sizeof(int), &alloc_size)) {
        return -1;
    }
    
    if (alloc_size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    entry->values = malloc(alloc_size);
    if (entry->values == NULL) {
        entry->capacity = 0;
        return -1;
    }
    
    if (num_values > 0 && values != NULL) {
        if (num_values > entry->capacity) {
            free(entry->values);
            entry->values = NULL;
            entry->capacity = 0;
            return -1;
        }
        size_t copy_size;
        if (!safe_multiply_size(num_values, sizeof(int), &copy_size)) {
            free(entry->values);
            entry->values = NULL;
            entry->capacity = 0;
            return -1;
        }
        if (copy_size > alloc_size) {
            free(entry->values);
            entry->values = NULL;
            entry->capacity = 0;
            return -1;
        }
        memcpy(entry->values, values, copy_size);
    }
    entry->size = num_values;
    dict->size++;
    return 0;
}

int dict_sort_list(Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    
    size_t key_len = strnlen(key, DICT_KEY_MAX);
    if (key_len == 0 || key_len >= DICT_KEY_MAX) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strncmp(dict->entries[i].key, key, DICT_KEY_MAX) == 0) {
            if (dict->entries[i].size > 1 && dict->entries[i].values != NULL) {
                qsort(dict->entries[i].values, 
                      dict->entries[i].size, 
                      sizeof(int), 
                      compare_ints);
            }
            return 0;
        }
    }
    return -1;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].values);
            dict->entries[i].values = NULL;
            dict->entries[i].size = 0;
            dict->entries[i].capacity = 0;
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->entries[i].key[0] != '\0') {
            printf("%s: [", dict->entries[i].key);
            for (size_t j = 0; j < dict->entries[i].size; j++) {
                printf("%d", dict->entries[i].values[j]);
                if (j < dict->entries[i].size - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    }
}

int main(void) {
    Dictionary dict;
    int result = EXIT_FAILURE;
    
    if (dict_init(&dict, DICT_INITIAL_CAPACITY) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    const int values1[] = {5, 2, 9, 1, 7};
    const int values2[] = {3, 8, 4};
    const int values3[] = {10, 6, 2, 8, 4, 1};
    
    if (dict_add_entry(&dict, "numbers", values1, 5) != 0 ||
        dict_add_entry(&dict, "primes", values2, 3) != 0 ||
        dict_add_entry(&dict, "mixed", values3, 6) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        goto cleanup;
    }
    
    printf("Before sorting:\n");
    dict_print(&dict);
    
    if (dict_sort_list(&dict, "numbers") != 0) {
        fprintf(stderr, "Failed to sort 'numbers'\n");
        goto cleanup;
    }
    
    if (dict_sort_list(&dict, "mixed") != 0) {
        fprintf(stderr, "Failed to sort 'mixed'\n");
        goto cleanup;
    }
    
    printf("\nAfter sorting 'numbers' and 'mixed':\n");
    dict_print(&dict);
    
    result = EXIT_SUCCESS;

cleanup:
    dict_free(&dict);
    return result;
}
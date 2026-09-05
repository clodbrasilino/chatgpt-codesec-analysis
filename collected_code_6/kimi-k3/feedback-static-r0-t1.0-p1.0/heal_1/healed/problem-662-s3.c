#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
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

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
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
    
    DictEntry *entry = &dict->entries[dict->size];
    size_t key_len = strlen(key);
    if (key_len >= sizeof(entry->key)) {
        return -1;
    }
    
    strncpy(entry->key, key, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    
    entry->capacity = num_values > 0 ? num_values : 1;
    entry->values = malloc(entry->capacity * sizeof(int));
    if (entry->values == NULL) {
        return -1;
    }
    
    if (num_values > 0) {
        memcpy(entry->values, values, num_values * sizeof(int));
    }
    entry->size = num_values;
    dict->size++;
    return 0;
}

int dict_sort_list(Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            if (dict->entries[i].size > 1) {
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
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
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

int main(void) {
    Dictionary dict;
    int result = EXIT_FAILURE;
    
    if (dict_init(&dict, 10) != 0) {
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
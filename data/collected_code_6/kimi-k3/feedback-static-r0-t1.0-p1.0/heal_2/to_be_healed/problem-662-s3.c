#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 63

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN + 1];
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

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
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
    
    size_t key_len = safe_strlen(key, MAX_KEY_LEN + 1);
    if (key_len > MAX_KEY_LEN) {
        return -1;
    }
    
    DictEntry *entry = &dict->entries[dict->size];
    
    if (key_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(entry->key, key, key_len);
    }
    entry->key[key_len] = '\0';
    
    entry->capacity = num_values > 0 ? num_values : 1;
    
    if (entry->capacity > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    entry->values = malloc(entry->capacity * sizeof(int));
    if (entry->values == NULL) {
        return -1;
    }
    
    if (num_values > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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
    
    size_t key_len = safe_strlen(key, MAX_KEY_LEN + 1);
    if (key_len > MAX_KEY_LEN) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strncmp(dict->entries[i].key, key, MAX_KEY_LEN + 1) == 0) {
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
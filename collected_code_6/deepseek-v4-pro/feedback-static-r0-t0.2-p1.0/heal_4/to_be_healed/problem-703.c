#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry **buckets;
    size_t capacity;
    size_t size;
} Dictionary;

static unsigned long hash_function(const char *key, size_t capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

Dictionary *dictionary_create(size_t capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->buckets = (Entry **)calloc(capacity, sizeof(Entry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->capacity = capacity;
    dict->size = 0;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return -1;
    }
    unsigned long index = hash_function(key, dict->capacity);
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    if (!new_entry) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    /* Possible weaknesses found:
     *  Assignment 'alloc_size=key_len+1', assigned value is greater than 0
     *  alloc_size is assigned 'key_len+1' here.
     */
    size_t alloc_size = key_len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=key_len' is always false
     *  Condition 'alloc_size<=key_len' is always false [knownConditionTrueFalse]
     */
    if (alloc_size <= key_len) {
        free(new_entry);
        return -1;
    }
    new_entry->key = (char *)malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!new_entry->key) {
        free(new_entry);
        return -1;
    }
    /* Possible weaknesses found:
     *  Condition 'alloc_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'alloc_size>0' is always true
     */
    if (alloc_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_entry->key, key, alloc_size);
    } else {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    dict->size++;
    return 0;
}

int dictionary_contains(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return 0;
    }
    unsigned long index = hash_function(key, dict->capacity);
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int dictionary_get(const Dictionary *dict, const char *key, int *value) {
    if (!dict || !key || !value) {
        return -1;
    }
    unsigned long index = hash_function(key, dict->capacity);
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

int dictionary_remove(Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return -1;
    }
    unsigned long index = hash_function(key, dict->capacity);
    Entry *current = dict->buckets[index];
    Entry *prev = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                dict->buckets[index] = current->next;
            }
            free(current->key);
            free(current);
            dict->size--;
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}

void dictionary_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *current = dict->buckets[i];
        while (current) {
            Entry *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);

    const char *test_keys[] = {"apple", "banana", "grape", "cherry", NULL};
    for (int i = 0; test_keys[i] != NULL; i++) {
        if (dictionary_contains(dict, test_keys[i])) {
            int val;
            dictionary_get(dict, test_keys[i], &val);
            printf("Key '%s' is present in the dictionary with value %d.\n", test_keys[i], val);
        } else {
            printf("Key '%s' is NOT present in the dictionary.\n", test_keys[i]);
        }
    }

    dictionary_remove(dict, "banana");
    printf("After removing 'banana':\n");
    const char *test_keys2[] = {"apple", "banana", "cherry", NULL};
    for (int i = 0; test_keys2[i] != NULL; i++) {
        if (dictionary_contains(dict, test_keys2[i])) {
            printf("Key '%s' is present in the dictionary.\n", test_keys2[i]);
        } else {
            printf("Key '%s' is NOT present in the dictionary.\n", test_keys2[i]);
        }
    }

    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}
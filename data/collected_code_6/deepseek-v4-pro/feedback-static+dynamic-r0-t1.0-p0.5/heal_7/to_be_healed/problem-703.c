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
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    const char *ptr = key;
    while (*ptr != '\0') {
        c = (unsigned char)*ptr;
        hash = ((hash << 5) + hash) + c;
        ptr++;
    }
    return hash % capacity;
}

Dictionary *dictionary_create(size_t capacity) {
    Dictionary *dict = NULL;
    Entry **buckets = NULL;

    if (capacity == 0) {
        return NULL;
    }

    dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    buckets = (Entry **)calloc(capacity, sizeof(Entry *));
    if (!buckets) {
        free(dict);
        return NULL;
    }

    dict->buckets = buckets;
    dict->capacity = capacity;
    dict->size = 0;
    return dict;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (!str) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    unsigned long index;
    Entry *current;
    Entry *new_entry;
    size_t key_len;
    char *key_copy;

    if (!dict || !key) {
        return -1;
    }

    key_len = safe_strlen(key, dict->capacity * 32);
    if (key_len == 0 && key[0] != '\0') {
        return -1;
    }

    index = hash_function(key, dict->capacity);
    current = dict->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }

    new_entry = (Entry *)malloc(sizeof(Entry));
    if (!new_entry) {
        return -1;
    }

    key_copy = (char *)malloc(key_len + 1);
    if (!key_copy) {
        free(new_entry);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len);
    key_copy[key_len] = '\0';

    new_entry->key = key_copy;
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    dict->size++;

    return 0;
}

int dictionary_contains(const Dictionary *dict, const char *key) {
    unsigned long index;
    Entry *current;

    if (!dict || !key) {
        return 0;
    }

    index = hash_function(key, dict->capacity);
    current = dict->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void dictionary_destroy(Dictionary *dict) {
    size_t i;
    Entry *current;
    Entry *temp;

    if (!dict) {
        return;
    }

    for (i = 0; i < dict->capacity; i++) {
        current = dict->buckets[i];
        while (current) {
            temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict;
    const char *keys_to_check[] = {"apple", "banana", "grape", "cherry", NULL};
    int i;

    dict = dictionary_create(16);
    if (!dict) {
        return 1;
    }

    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);

    for (i = 0; keys_to_check[i] != NULL; i++) {
        if (dictionary_contains(dict, keys_to_check[i])) {
            printf("Key '%s' is present in the dictionary.\n", keys_to_check[i]);
        } else {
            printf("Key '%s' is NOT present in the dictionary.\n", keys_to_check[i]);
        }
    }

    dictionary_destroy(dict);
    return 0;
}
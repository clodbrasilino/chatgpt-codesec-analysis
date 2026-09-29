#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry **buckets;
    size_t size;
} Dictionary;

static unsigned long hash_function(const char *str, size_t size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Dictionary *create_dictionary(size_t size) {
    Dictionary *dict;
    if (size == 0) {
        return NULL;
    }
    dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->buckets = (DictEntry **)calloc(size, sizeof(DictEntry *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    size_t i;
    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        DictEntry *entry = dict->buckets[i];
        while (entry != NULL) {
            DictEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
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

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    size_t key_len;
    unsigned long index;
    DictEntry *current;
    char *key_copy;
    DictEntry *new_entry;
    size_t max_key_len;

    if (dict == NULL || key == NULL) {
        return -1;
    }
    max_key_len = dict->size * 16;
    if (max_key_len == 0) {
        return -1;
    }
    key_len = safe_strlen(key, max_key_len);
    if (key_len >= max_key_len) {
        return -1;
    }
    if (key_len == 0 && key[0] != '\0') {
        return -1;
    }
    index = hash_function(key, dict->size);
    current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return -1;
    }
    if (key_len >= SIZE_MAX) {
        free(new_entry);
        return -1;
    }
    key_copy = (char *)malloc(key_len + 1);
    if (key_copy == NULL) {
        free(new_entry);
        return -1;
    }
    if (key_len > 0) {
        if (key_len > SIZE_MAX - 1) {
            free(key_copy);
            free(new_entry);
            return -1;
        }
        if (key_copy + key_len < key_copy) {
            free(key_copy);
            free(new_entry);
            return -1;
        }
        memcpy(key_copy, key, key_len);
    }
    key_copy[key_len] = '\0';
    new_entry->key = key_copy;
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 0;
}

int dictionary_get(Dictionary *dict, const char *key, int *value) {
    unsigned long index;
    DictEntry *current;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    index = hash_function(key, dict->size);
    current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

Dictionary *merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    size_t i;
    size_t new_size;
    Dictionary *merged;

    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    if (dict1->size > SIZE_MAX - dict2->size) {
        return NULL;
    }
    new_size = dict1->size + dict2->size;
    if (new_size == 0) {
        return NULL;
    }
    merged = create_dictionary(new_size);
    if (merged == NULL) {
        return NULL;
    }
    for (i = 0; i < dict1->size; i++) {
        DictEntry *entry = dict1->buckets[i];
        while (entry != NULL) {
            if (dictionary_insert(merged, entry->key, entry->value) != 0) {
                destroy_dictionary(merged);
                return NULL;
            }
            entry = entry->next;
        }
    }
    for (i = 0; i < dict2->size; i++) {
        DictEntry *entry = dict2->buckets[i];
        while (entry != NULL) {
            if (dictionary_insert(merged, entry->key, entry->value) != 0) {
                destroy_dictionary(merged);
                return NULL;
            }
            entry = entry->next;
        }
    }
    return merged;
}

void print_dictionary(Dictionary *dict) {
    size_t i;
    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        DictEntry *entry = dict->buckets[i];
        while (entry != NULL) {
            printf("%s: %d\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

int main(void) {
    Dictionary *dict1 = create_dictionary(10);
    Dictionary *dict2 = create_dictionary(10);
    if (dict1 == NULL || dict2 == NULL) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        return 1;
    }
    dictionary_insert(dict1, "apple", 5);
    dictionary_insert(dict1, "banana", 7);
    dictionary_insert(dict2, "cherry", 9);
    dictionary_insert(dict2, "apple", 10);
    {
        Dictionary *merged = merge_dictionaries(dict1, dict2);
        if (merged == NULL) {
            destroy_dictionary(dict1);
            destroy_dictionary(dict2);
            return 1;
        }
        print_dictionary(merged);
        destroy_dictionary(merged);
    }
    destroy_dictionary(dict1);
    destroy_dictionary(dict2);
    return 0;
}
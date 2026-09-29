#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Dictionary *create_dictionary(size_t size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
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
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
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

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    unsigned long index = hash_function(key, dict->size);
    DictEntry *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    DictEntry *new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return -1;
    }
    new_entry->key = (char *)malloc(strlen(key) + 1);
    if (new_entry->key == NULL) {
        free(new_entry);
        return -1;
    }
    strcpy(new_entry->key, key);
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 0;
}

int dictionary_get(Dictionary *dict, const char *key, int *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    unsigned long index = hash_function(key, dict->size);
    DictEntry *current = dict->buckets[index];
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
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    size_t new_size = dict1->size + dict2->size;
    Dictionary *merged = create_dictionary(new_size);
    if (merged == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < dict1->size; i++) {
        DictEntry *entry = dict1->buckets[i];
        while (entry != NULL) {
            if (dictionary_insert(merged, entry->key, entry->value) != 0) {
                destroy_dictionary(merged);
                return NULL;
            }
            entry = entry->next;
        }
    }
    for (size_t i = 0; i < dict2->size; i++) {
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

int main(void) {
    Dictionary *dict1 = create_dictionary(10);
    Dictionary *dict2 = create_dictionary(10);
    if (dict1 == NULL || dict2 == NULL) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        return 1;
    }
    dictionary_insert(dict1, "apple", 1);
    dictionary_insert(dict1, "banana", 2);
    dictionary_insert(dict2, "banana", 3);
    dictionary_insert(dict2, "cherry", 4);
    Dictionary *merged = merge_dictionaries(dict1, dict2);
    if (merged == NULL) {
        destroy_dictionary(dict1);
        destroy_dictionary(dict2);
        return 1;
    }
    int value;
    if (dictionary_get(merged, "apple", &value) == 0) {
        printf("apple: %d\n", value);
    }
    if (dictionary_get(merged, "banana", &value) == 0) {
        printf("banana: %d\n", value);
    }
    if (dictionary_get(merged, "cherry", &value) == 0) {
        printf("cherry: %d\n", value);
    }
    destroy_dictionary(dict1);
    destroy_dictionary(dict2);
    destroy_dictionary(merged);
    return 0;
}
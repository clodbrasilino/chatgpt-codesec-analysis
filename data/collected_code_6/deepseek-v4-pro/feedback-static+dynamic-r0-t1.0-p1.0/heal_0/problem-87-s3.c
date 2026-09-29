#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 8
#define LOAD_FACTOR 0.75

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry **buckets;
    size_t size;
    size_t capacity;
} Dictionary;

static unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static char *duplicate_string(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = (char *)malloc(len);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, str, len);
    return copy;
}

static Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->capacity = INITIAL_SIZE;
    dict->size = 0;
    dict->buckets = (Entry **)calloc(dict->capacity, sizeof(Entry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    return dict;
}

static int dictionary_resize(Dictionary *dict) {
    size_t new_capacity = dict->capacity * 2;
    Entry **new_buckets = (Entry **)calloc(new_capacity, sizeof(Entry *));
    if (!new_buckets) {
        return 0;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            unsigned long idx = hash_function(entry->key) % new_capacity;
            entry->next = new_buckets[idx];
            new_buckets[idx] = entry;
            entry = next;
        }
    }
    
    free(dict->buckets);
    dict->buckets = new_buckets;
    dict->capacity = new_capacity;
    return 1;
}

static int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return 0;
    }
    
    if ((double)(dict->size + 1) / dict->capacity > LOAD_FACTOR) {
        if (!dictionary_resize(dict)) {
            return 0;
        }
    }
    
    unsigned long idx = hash_function(key) % dict->capacity;
    
    Entry *current = dict->buckets[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 1;
        }
        current = current->next;
    }
    
    char *key_copy = duplicate_string(key);
    if (!key_copy) {
        return 0;
    }
    
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    if (!new_entry) {
        free(key_copy);
        return 0;
    }
    
    new_entry->key = key_copy;
    new_entry->value = value;
    new_entry->next = dict->buckets[idx];
    dict->buckets[idx] = new_entry;
    dict->size++;
    
    return 1;
}

static int dictionary_get(const Dictionary *dict, const char *key, int *value) {
    if (!dict || !key || !value) {
        return 0;
    }
    
    unsigned long idx = hash_function(key) % dict->capacity;
    Entry *current = dict->buckets[idx];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

static int dictionary_contains(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return 0;
    }
    
    unsigned long idx = hash_function(key) % dict->capacity;
    Entry *current = dict->buckets[idx];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

static void dictionary_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    
    free(dict->buckets);
    free(dict);
}

static Dictionary *merge_three_dictionaries(const Dictionary *dict1, 
                                             const Dictionary *dict2, 
                                             const Dictionary *dict3) {
    if (!dict1 || !dict2 || !dict3) {
        return NULL;
    }
    
    Dictionary *merged = create_dictionary();
    if (!merged) {
        return NULL;
    }
    
    const Dictionary *dicts[3] = {dict1, dict2, dict3};
    
    for (int d = 0; d < 3; d++) {
        for (size_t i = 0; i < dicts[d]->capacity; i++) {
            Entry *entry = dicts[d]->buckets[i];
            while (entry) {
                if (!dictionary_insert(merged, entry->key, entry->value)) {
                    dictionary_destroy(merged);
                    return NULL;
                }
                entry = entry->next;
            }
        }
    }
    
    return merged;
}

static void dictionary_print(const Dictionary *dict) {
    if (!dict) {
        printf("Dictionary is NULL\n");
        return;
    }
    
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            printf("%s: %d\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

int main(void) {
    Dictionary *dict1 = create_dictionary();
    Dictionary *dict2 = create_dictionary();
    Dictionary *dict3 = create_dictionary();
    
    if (!dict1 || !dict2 || !dict3) {
        dictionary_destroy(dict1);
        dictionary_destroy(dict2);
        dictionary_destroy(dict3);
        return 1;
    }
    
    dictionary_insert(dict1, "a", 1);
    dictionary_insert(dict1, "b", 2);
    dictionary_insert(dict1, "c", 3);
    
    dictionary_insert(dict2, "c", 30);
    dictionary_insert(dict2, "d", 4);
    dictionary_insert(dict2, "e", 5);
    
    dictionary_insert(dict3, "e", 50);
    dictionary_insert(dict3, "f", 6);
    dictionary_insert(dict3, "g", 7);
    
    Dictionary *merged = merge_three_dictionaries(dict1, dict2, dict3);
    if (!merged) {
        dictionary_destroy(dict1);
        dictionary_destroy(dict2);
        dictionary_destroy(dict3);
        return 1;
    }
    
    printf("Merged dictionary:\n");
    dictionary_print(merged);
    
    int value;
    if (dictionary_get(merged, "c", &value)) {
        printf("Value of 'c' in merged: %d\n", value);
    }
    
    if (dictionary_contains(merged, "f")) {
        printf("'f' exists in merged dictionary\n");
    }
    
    dictionary_destroy(merged);
    dictionary_destroy(dict1);
    dictionary_destroy(dict2);
    dictionary_destroy(dict3);
    
    return 0;
}
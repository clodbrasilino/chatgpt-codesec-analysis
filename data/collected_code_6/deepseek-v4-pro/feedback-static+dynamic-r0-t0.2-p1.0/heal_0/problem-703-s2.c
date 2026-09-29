#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue **buckets;
    size_t bucket_count;
} Dictionary;

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Dictionary *dictionary_create(size_t bucket_count) {
    Dictionary *dict = malloc(sizeof(*dict));
    if (!dict) {
        return NULL;
    }
    dict->buckets = calloc(bucket_count, sizeof(KeyValue *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->bucket_count = bucket_count;
    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->bucket_count; i++) {
        KeyValue *entry = dict->buckets[i];
        while (entry) {
            KeyValue *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return 0;
    }
    unsigned long hash = hash_string(key);
    size_t index = hash % dict->bucket_count;

    KeyValue *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return 1;
        }
        entry = entry->next;
    }

    KeyValue *new_entry = malloc(sizeof(*new_entry));
    if (!new_entry) {
        return 0;
    }
    new_entry->key = malloc(strlen(key) + 1);
    if (!new_entry->key) {
        free(new_entry);
        return 0;
    }
    strcpy(new_entry->key, key);
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 1;
}

int dictionary_contains(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return 0;
    }
    unsigned long hash = hash_string(key);
    size_t index = hash % dict->bucket_count;

    KeyValue *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return 1;
        }
        entry = entry->next;
    }
    return 0;
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (!dict) {
        return 1;
    }

    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);

    const char *test_keys[] = {"apple", "banana", "grape", "cherry", NULL};
    for (int i = 0; test_keys[i] != NULL; i++) {
        if (dictionary_contains(dict, test_keys[i])) {
            printf("%s is present\n", test_keys[i]);
        } else {
            printf("%s is not present\n", test_keys[i]);
        }
    }

    dictionary_destroy(dict);
    return 0;
}
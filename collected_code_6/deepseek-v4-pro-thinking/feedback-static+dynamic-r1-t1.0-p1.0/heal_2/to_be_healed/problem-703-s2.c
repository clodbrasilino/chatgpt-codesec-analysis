#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DICTIONARY_CAPACITY 101
#define MAX_STRING_LENGTH  1024

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry *buckets[DICTIONARY_CAPACITY];
} Dictionary;

static unsigned int hash_string(const char *key) {
    unsigned int hash = 5381;
    while (*key) {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
        key++;
    }
    return hash % DICTIONARY_CAPACITY;
}

static char *duplicate_string(const char *str) {
    size_t len = 0;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    while (len < MAX_STRING_LENGTH && str[len] != '\0') {
        len++;
    }

    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len + 1);
    return copy;
}

Dictionary *dictionary_create(void) {
    Dictionary *dict = malloc(sizeof(*dict));
    size_t i;

    if (dict == NULL) {
        return NULL;
    }

    for (i = 0; i < DICTIONARY_CAPACITY; i++) {
        dict->buckets[i] = NULL;
    }

    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    size_t i;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < DICTIONARY_CAPACITY; i++) {
        Entry *entry = dict->buckets[i];
        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }

    free(dict);
}

bool dictionary_insert(Dictionary *dict, const char *key, int value) {
    unsigned int index;
    Entry *current;
    char *key_copy;
    Entry *new_entry;

    if (dict == NULL || key == NULL) {
        return false;
    }

    index = hash_string(key);
    current = dict->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return true;
        }
        current = current->next;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    new_entry = malloc(sizeof(*new_entry));
    if (new_entry == NULL) {
        free(key_copy);
        return false;
    }

    new_entry->key = key_copy;
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;

    return true;
}

bool dictionary_contains(const Dictionary *dict, const char *key) {
    unsigned int index;
    const Entry *current;

    if (dict == NULL || key == NULL) {
        return false;
    }

    index = hash_string(key);
    current = dict->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}

int main(void) {
    Dictionary *dict = dictionary_create();

    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    if (!dictionary_insert(dict, "apple", 1)) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }

    if (!dictionary_insert(dict, "banana", 2)) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("%d\n", dictionary_contains(dict, "apple"));
    printf("%d\n", dictionary_contains(dict, "banana"));
    printf("%d\n", dictionary_contains(dict, "cherry"));

    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}
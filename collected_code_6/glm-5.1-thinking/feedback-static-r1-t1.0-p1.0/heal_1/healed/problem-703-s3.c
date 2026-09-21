#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
} Dictionary;

static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

static char *duplicate_string(const char *s) {
    int len = snprintf(NULL, 0, "%s", s);
    if (len < 0) {
        return NULL;
    }
    size_t size = (size_t)len + 1;
    char *copy = malloc(size);
    if (copy) {
        snprintf(copy, size, "%s", s);
    }
    return copy;
}

Dictionary *dict_create(void) {
    Dictionary *dict = calloc(1, sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    return dict;
}

void dict_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(dict);
}

int dict_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) {
        return 0;
    }
    unsigned long index = hash(key);
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            char *new_value = duplicate_string(value);
            if (!new_value) {
                return 0;
            }
            free(entry->value);
            entry->value = new_value;
            return 1;
        }
        entry = entry->next;
    }
    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) {
        return 0;
    }
    new_entry->key = duplicate_string(key);
    if (!new_entry->key) {
        free(new_entry);
        return 0;
    }
    new_entry->value = duplicate_string(value);
    if (!new_entry->value) {
        free(new_entry->key);
        free(new_entry);
        return 0;
    }
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 1;
}

int dict_contains(const Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return 0;
    }
    unsigned long index = hash(key);
    const Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return 1;
        }
        entry = entry->next;
    }
    return 0;
}

int main(void) {
    Dictionary *dict = dict_create();
    if (!dict) {
        return EXIT_FAILURE;
    }
    if (!dict_insert(dict, "hello", "world")) {
        dict_destroy(dict);
        return EXIT_FAILURE;
    }
    if (!dict_insert(dict, "foo", "bar")) {
        dict_destroy(dict);
        return EXIT_FAILURE;
    }
    if (dict_contains(dict, "hello")) {
        printf("Key 'hello' found.\n");
    } else {
        printf("Key 'hello' not found.\n");
    }
    if (dict_contains(dict, "missing")) {
        printf("Key 'missing' found.\n");
    } else {
        printf("Key 'missing' not found.\n");
    }
    dict_destroy(dict);
    return EXIT_SUCCESS;
}